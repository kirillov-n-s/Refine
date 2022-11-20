#ifndef REFINE_GEOMETRY_TRIMESH_H
#define REFINE_GEOMETRY_TRIMESH_H

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace Refine::Geometry {

    class TriMesh
    {
    public:
        TriMesh() = default;
        TriMesh(const TriMesh &) = default;

        TriMesh(
            const std::vector<glm::vec3> &vertices,
            const std::vector<int> &vertexIndices,
            const std::vector<glm::vec3> &normals = {},
            const std::vector<glm::vec2> &texcoords = {},
            const std::vector<int> &texcoordIndices = {});

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texcoords;

        std::vector<int> vertexIndices;
        std::vector<int> texcoordIndices;
    };

    bool operator==(const TriMesh &lhs, const TriMesh &rhs);
    bool operator!=(const TriMesh &lhs, const TriMesh &rhs);
}

#endif
