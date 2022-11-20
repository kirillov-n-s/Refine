#ifndef REFINE_GEOMETRY_POLYMESH_H
#define REFINE_GEOMETRY_POLYMESH_H

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace Refine::Geometry {

    class PolyMesh
    {
    public:
        PolyMesh() = default;
        PolyMesh(const PolyMesh &) = default;

        PolyMesh(
                const std::vector<glm::vec3> &vertices,
                const std::vector<int> &vertexIndices,
                const std::vector<int> &polygonStarts,
                const std::vector<glm::vec3> &normals = {},
                const std::vector<glm::vec2> &texcoords = {},
                const std::vector<int> &texcoordIndices = {});

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texcoords;

        std::vector<int> vertexIndices;
        std::vector<int> texcoordIndices;

        std::vector<int> polygonStarts;
    };

    bool operator==(const PolyMesh &lhs, const PolyMesh &rhs);
    bool operator!=(const PolyMesh &lhs, const PolyMesh &rhs);
}

#endif
