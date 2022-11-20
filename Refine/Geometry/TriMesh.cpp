#include "TriMesh.h"
#include <algorithm>

namespace Refine::Geometry {

    TriMesh::TriMesh(const std::vector<glm::vec3> &vertices,
                     const std::vector<int> &vertexIndices,
                     const std::vector<glm::vec3> &normals,
                     const std::vector<glm::vec2> &texcoords,
                     const std::vector<int> &texcoordIndices)
        : vertices(vertices),
          vertexIndices(vertexIndices),
          normals(normals),
          texcoords(texcoords),
          texcoordIndices(texcoordIndices)
    {}

    bool operator==(const TriMesh &lhs, const TriMesh &rhs)
    {
        return lhs.vertices == rhs.vertices
            && lhs.vertexIndices == rhs.vertexIndices
            && lhs.normals == rhs.normals
            && lhs.texcoords == rhs.texcoords
            && lhs.texcoordIndices == rhs.texcoordIndices;
    }

    bool operator!=(const TriMesh &lhs, const TriMesh &rhs)
    {
        return !(lhs == rhs);
    }
}
