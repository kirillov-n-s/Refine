#include <glm/gtc/epsilon.hpp>
#include "PolyMesh.h"
#include "../Common/Common.h"

namespace Refine::Geometry {

    PolyMesh::PolyMesh(
            const std::vector<glm::vec3> &vertices,
            const std::vector<int> &vertexIndices,
            const std::vector<int> &polygonStarts,
            const std::vector<glm::vec3> &normals,
            const std::vector<glm::vec2> &texcoords,
            const std::vector<int> &texcoordIndices)
        : vertices(vertices),
          vertexIndices(vertexIndices),
          polygonStarts(polygonStarts),
          normals(normals),
          texcoords(texcoords),
          texcoordIndices(texcoordIndices)
    {}

    bool operator==(const PolyMesh &lhs, const PolyMesh &rhs)
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

    bool operator!=(const PolyMesh &lhs, const PolyMesh &rhs)
    {
        return !(lhs == rhs);
    }
}
