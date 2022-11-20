#ifndef REFINE_GEOMETRY_MESHPOLY_H
#define REFINE_GEOMETRY_MESHPOLY_H

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace Refine::Geometry {

    class MeshPoly
    {
    public:
        MeshPoly() = default;
        MeshPoly(const MeshPoly &) = default;

        MeshPoly(
                std::vector<glm::vec3> vertices,
                std::vector<int> vertexIndices,
                std::vector<int> polygonStarts,
                std::vector<glm::vec3> normals = {},
                std::vector<glm::vec2> texcoords = {},
                std::vector<int> texcoordIndices = {});

        bool hasTexcoords() const;
        bool hasNormals() const;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texcoords;

        std::vector<int> vertexIndices;
        std::vector<int> texcoordIndices;

        std::vector<int> polygonStarts;
    };

    bool operator==(const MeshPoly &lhs, const MeshPoly &rhs);
    bool operator!=(const MeshPoly &lhs, const MeshPoly &rhs);
}

#endif
