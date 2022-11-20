#ifndef REFINE_GEOMETRY_MESHTRI_H
#define REFINE_GEOMETRY_MESHTRI_H

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace Refine::Geometry {

    class MeshTri
    {
    public:
        MeshTri() = default;
        MeshTri(const MeshTri &) = default;

        MeshTri(
            std::vector<glm::vec3> vertices,
            std::vector<int> vertexIndices,
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
    };

    bool operator==(const MeshTri &lhs, const MeshTri &rhs);
    bool operator!=(const MeshTri &lhs, const MeshTri &rhs);
}

#endif
