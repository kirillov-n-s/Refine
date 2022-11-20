#include "Common.h"
#include "MeshTri.h"

namespace Refine::Geometry {

    MeshTri::MeshTri(std::vector<glm::vec3> vertices,
                     std::vector<int> vertexIndices,
                     std::vector<glm::vec3> normals,
                     std::vector<glm::vec2> texcoords,
                     std::vector<int> texcoordIndices)
        : vertices(std::move(vertices)),
          vertexIndices(std::move(vertexIndices)),
          normals(std::move(normals)),
          texcoords(std::move(texcoords)),
          texcoordIndices(std::move(texcoordIndices))
    {
        if (this->normals.empty())
            this->normals = computeNormals(this->vertices, this->vertexIndices);
    }

    bool MeshTri::hasTexcoords() const
    {
        return !texcoords.empty() && !texcoordIndices.empty();
    }

    bool MeshTri::hasNormals() const
    {
        return !normals.empty();
    }

    bool operator==(const MeshTri &lhs, const MeshTri &rhs)
    {
        return lhs.vertices == rhs.vertices
            && lhs.vertexIndices == rhs.vertexIndices
            && lhs.normals == rhs.normals
            && lhs.texcoords == rhs.texcoords
            && lhs.texcoordIndices == rhs.texcoordIndices;
    }

    bool operator!=(const MeshTri &lhs, const MeshTri &rhs)
    {
        return !(lhs == rhs);
    }
}
