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
            pathMeshes + "sphere.obj",
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

    std::vector<Refine::Rendering::Point> points;
    std::vector<unsigned int> indices;
    Refine::Rendering::glBuffers(meshTri, points, indices);

    const int nVertices = meshTri.vertices.size();
    std::vector<float> masses(nVertices, 1.0f);
    //masses.front() = INFINITY;
    masses.back() = INFINITY;
    auto *problem = new Refine::PBD::ProblemPositional(meshTri.vertices, masses, 1, 500);
    problem->addForce(new Refine::PBD::ForceConstant());
    problem->addConstraint(new Refine::PBD::ConstraintBox(glm::vec3(-1.5f), glm::vec3(5.0f)));
    const std::vector<std::pair<int, int>> edges =
            Refine::Geometry::Adjacency::vertexToVertexPairsSymmetric(meshTri.vertexIndices);
    problem->addConstraint(new Refine::PBD::ConstraintDistance(meshTri.vertices, edges));

    Demo::create(1600, 900, error);
    Refine::Common::exitOnError(error, 2);

    auto* glMesh = new Refine::Rendering::GlMesh(points, indices);
    auto* glShader = new Refine::Rendering::GlShader(
            pathShaders + "main.vert",
            pathShaders + "main.frag",
            error);
    Refine::Common::exitOnError(error, 3);

    Demo::load(
            &meshTri,
            problem,
            glMesh,
            glShader);
    Demo::run();
    Demo::destroy();
}