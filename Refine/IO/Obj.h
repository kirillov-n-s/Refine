#ifndef REFINE_IO_OBJ_H
#define REFINE_IO_OBJ_H

#include <string>
#include "../Geometry/MeshPoly.h"

namespace Refine::IO {

    struct SettingsObjReader
    {
        bool errorOnVertex4NotOne = true;
        bool errorOnTexcoord3NotZero = true;
        bool readTexcoords = true;
    };

    struct SettingsObjWriter
    {
        bool writeTexcoords = true;
        bool writeNormals = true;
    };

    Geometry::MeshPoly readObj(
            const std::string &path,
            std::string &error,
            const SettingsObjReader &settings = {});

    void writeObj(
            const Geometry::MeshPoly &mesh,
            const std::string &path,
            std::string &error,
            const SettingsObjWriter &settings = {});
}

#endif
