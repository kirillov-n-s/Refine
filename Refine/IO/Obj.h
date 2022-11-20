#ifndef REFINE_IO_OBJ_H
#define REFINE_IO_OBJ_H

#include <string>
#include "../Geometry/PolyMesh.h"

namespace Refine::IO {

    struct SettingsObjReader
    {
        bool errorOnVertex4thNotOne = true;
        bool errorOnTexcoord3rdNotZero = true;
    };

    Geometry::PolyMesh readObj(
            const std::string &path,
            std::string &error,
            const SettingsObjReader &settings = {});
    void writeObj(
        const Geometry::PolyMesh &mesh,
        const std::string &path,
        std::string &error);
}

#endif
