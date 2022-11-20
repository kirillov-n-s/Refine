#include <iostream>
#include "Refine/Common/Debug.h"
#include "Refine/Geometry/Common.h"
#include "Refine/IO/Obj.h"
#include "Refine/Rendering/GlMesh.h"
#include "Refine/Rendering/GlShader.h"
#include "Demo.h"

int main()
{
    const std::string path = "../data/";
    const std::string pathMeshes = path + "meshes/";
    const std::string pathShaders = path + "shaders/";

    std::string error = "";
    const Refine::Geometry::MeshPoly meshPoly =
            Refine::IO::readObj(pathMeshes + "read/case.obj", error);
    Refine::Common::exitOnError(error, 1);

    const Refine::Geometry::MeshTri meshTri(
            meshPoly.vertices,
            Refine::Geometry::triangulate(meshPoly.vertexIndices, meshPoly.polygonStarts),
            {},
            meshPoly.texcoords,
            meshPoly.hasTexcoords()
            ? Refine::Geometry::triangulate(meshPoly.texcoordIndices, meshPoly.polygonStarts)
            : std::vector<int> {});

    std::vector<Refine::Rendering::Point> points;
    std::vector<unsigned int> indices;
    Refine::Rendering::glBuffers(
            meshTri,
            points,
            indices);

    Demo::create(1600, 900, error);
    Refine::Common::exitOnError(error, 2);
    auto* glMesh = new Refine::Rendering::GlMesh(points, indices);
    auto* glShader = new Refine::Rendering::GlShader(
            pathShaders + "main.vert",
            pathShaders + "main.frag",
            error);
    Refine::Common::exitOnError(error, 3);
    Demo::load(
            glMesh,
            glShader,
            Refine::Rendering::Camera {});
    Demo::run();
    Demo::destroy();
}