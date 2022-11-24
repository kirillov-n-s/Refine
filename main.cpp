#include "Refine/Common/Debug.h"
#include "Refine/Geometry/Common.h"
#include "Refine/IO/Obj.h"
#include "Refine/Rendering/GlMesh.h"
#include "Refine/Rendering/GlShader.h"
#include "Refine/Geometry/Adjacency.h"
#include "Demo.h"

int main()
{
    const std::string path = "../data/";
    const std::string pathMeshes = path + "meshes/";
    const std::string pathShaders = path + "shaders/";

    std::string error = "";
    const Refine::Geometry::MeshPoly meshPoly = Refine::IO::readObj(
            pathMeshes + "WrapHead.obj",
            error,
            Refine::IO::SettingsObjReader
            {
                .readTexcoords = false
            });
    Refine::Common::exitOnError(error, 1);

    Refine::Geometry::MeshTri meshTri(
            meshPoly.vertices,
            Refine::Geometry::triangulate(meshPoly.vertexIndices, meshPoly.polygonStarts),
            {},
            meshPoly.texcoords,
            meshPoly.hasTexcoords()
            ? Refine::Geometry::triangulate(meshPoly.texcoordIndices, meshPoly.polygonStarts)
            : std::vector<int> {});

    const int nVertices = meshTri.vertices.size();
    std::vector<float> weights(nVertices, 1.0f);
    //weights.front() = 0.0f;

    const Refine::Spatial::AABB aabb {
        .min = glm::vec3(-4.0f, -6.0f, -4.0f),
        .max = glm::vec3(4.0f, 6.0f, 4.0f)
    };
    Refine::PBD::ProblemPositional problem(
            meshTri.vertices,
            weights,
            aabb,
            5,
            10);
    problem.addForce(new Refine::PBD::ForceConstant());

    const std::vector<Refine::Geometry::Adjacency::Edge> edges =
            Refine::Geometry::Adjacency::vertexToVertexAsEdges(meshTri.vertexIndices);
    problem.addConstraint(new Refine::PBD::ConstraintARAP(meshTri.vertices, edges, 0.0001f));
    //problem.addConstraint(new Refine::PBD::ConstraintDistance(meshTri.vertices, edges, 0.005f));

    /*const std::vector<Refine::Geometry::Adjacency::Dihedral> dihedrals =
            Refine::Geometry::Adjacency::triangleToTriangleAsDihedrals(meshTri.vertexIndices);
    problem.addConstraint(new Refine::PBD::ConstraintDihedral(meshTri.vertices, dihedrals, 0.005f));*/

    Refine::Rendering::Buffer glBuffer(meshTri);

    Demo::create(1600, 900, error);
    Refine::Common::exitOnError(error, 2);

    Refine::Rendering::GlMesh glMesh(glBuffer);
    Refine::Rendering::GlShader glShader(
            pathShaders + "main.vert",
            pathShaders + "main.frag",
            error);
    Refine::Common::exitOnError(error, 3);

    Demo::load(
            &meshTri,
            &problem,
            &glBuffer,
            &glMesh,
            &glShader);
    Demo::run();
    Demo::destroy();
}