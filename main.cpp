#include <iostream>
#include "Refine/Common/Debug.h"
#include "Refine/IO/Obj.h"

int main()
{
    const std::string name = "cube.obj";

    const std::string pathRead = "../data/meshes/read/" + name;
    std::string error;
    const Refine::Geometry::PolyMesh mesh = Refine::IO::readObj(pathRead, error);
    Refine::Common::exitOnError(error, 1);

    const std::string pathWrite = "../data/meshes/write2/" + name;
    Refine::IO::writeObj(mesh, pathWrite, error);
    Refine::Common::exitOnError(error, 2);

    const Refine::Geometry::PolyMesh meshReadWrite = Refine::IO::readObj(pathWrite, error);
    Refine::Common::exitOnError(error, 3);

    std::cout << std::boolalpha << (mesh == meshReadWrite) << std::endl;
}