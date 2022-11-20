#include "MeshPoly.h"

#include <utility>
#include "../Common/Common.h"

namespace Refine::Geometry {

    MeshPoly::MeshPoly(
            std::vector<glm::vec3> vertices,
            std::vector<int> vertexIndices,
            std::vector<int> polygonStarts,
            std::vector<glm::vec3> normals,
            std::vector<glm::vec2> texcoords,
            std::vector<int> texcoordIndices)
        : vertices(std::move(vertices)),
          vertexIndices(std::move(vertexIndices)),
          polygonStarts(std::move(polygonStarts)),
          normals(std::move(normals)),
          texcoords(std::move(texcoords)),
          texcoordIndices(std::move(texcoordIndices))
    {}

    bool MeshPoly::hasTexcoords() const
    {
        return !texcoords.empty() && !texcoordIndices.empty();
    }

    bool MeshPoly::hasNormals() const
    {
        return !normals.empty();
    }

    bool operator==(const MeshPoly &lhs, const MeshPoly &rhs)
    {
        const bool areSizesEqual = lhs.vertices.size() == rhs.vertices.size()
                && lhs.vertexIndices.size() == rhs.vertexIndices.size()
                && lhs.polygonStarts.size() == rhs.polygonStarts.size()
                && lhs.normals.size() == rhs.normals.size()
                && lhs.texcoords.size() == rhs.texcoords.size()
                && lhs.texcoordIndices.size() == rhs.texcoordIndices.size();
        if (!areSizesEqual)
            return false;

        const bool areVerticesEqual = std::equal(
                lhs.vertices.begin(),
                lhs.vertices.end(),
                rhs.vertices.begin(),
                Common::fuzzyCompare<glm::vec3>);
        if (!areVerticesEqual)
            return false;

        const bool areNormalsEqual = std::equal(
                lhs.normals.begin(),
                lhs.normals.end(),
                rhs.normals.begin(),
                Common::fuzzyCompare<glm::vec3>);
        if (!areNormalsEqual)
            return false;

        const bool areTexcoordsEqual = std::equal(
                lhs.texcoords.begin(),
                lhs.texcoords.end(),
                rhs.texcoords.begin(),
                Common::fuzzyCompare<glm::vec2>);
        if (!areTexcoordsEqual)
            return false;

        return lhs.vertexIndices == rhs.vertexIndices
               && lhs.polygonStarts == rhs.polygonStarts
               && lhs.texcoordIndices == rhs.texcoordIndices;
    }

    bool operator!=(const MeshPoly &lhs, const MeshPoly &rhs)
    {
        return !(lhs == rhs);
    }
}
