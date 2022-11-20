#include <unordered_map>
#include "Common.h"

namespace Refine::Rendering {

    Index makeIndex(
            const Geometry::MeshTri &mesh,
            const int flatIndex)
    {
        return {
                .vertex = mesh.vertexIndices[flatIndex],

                .texcoord = mesh.hasTexcoords()
                ? mesh.texcoordIndices[flatIndex]
                : -1,

                .normal = mesh.hasNormals()
                ? mesh.vertexIndices[flatIndex]
                : -1
        };
    }

    Point pointAtIndex(
            const Geometry::MeshTri &mesh,
            const Index &index)
    {
        return {
                .vertex = mesh.vertices[index.vertex],

                .texcoord = index.texcoord != -1
                ? mesh.texcoords[index.texcoord]
                : glm::vec3 { 0.f },

                .normal = index.normal != -1
                ? mesh.normals[index.normal]
                : glm::vec3 { 0.f }
        };
    }

    bool operator==(
            const Index &lhs,
            const Index &rhs)
    {
        return lhs.vertex == rhs.vertex
               && lhs.texcoord == rhs.texcoord
               && lhs.normal == rhs.normal;
    }

    bool operator!=(
            const Index &lhs,
            const Index &rhs)
    {
        return !(lhs == rhs);
    }

    bool operator==(
            const Point &lhs,
            const Point &rhs)
    {
        return lhs.vertex == rhs.vertex
               && lhs.texcoord == rhs.texcoord
               && lhs.normal == rhs.normal;
    }

    bool operator!=(
            const Point &lhs,
            const Point &rhs)
    {
        return !(lhs == rhs);
    }

    void glBuffers(
            const Geometry::MeshTri &mesh,
            std::vector<Point> &points,
            std::vector<unsigned int> &indices)
    {
        std::unordered_map<Index, unsigned int> indToBufferIndMap;
        const int nFlatIndices = mesh.vertexIndices.size();
        for (int flatInd = 0; flatInd < nFlatIndices; flatInd++) {

            const Index& index = makeIndex(mesh, flatInd);

            const auto &mapPairIt = indToBufferIndMap.find(index);
            if (mapPairIt != indToBufferIndMap.end()) {
                indices.push_back(mapPairIt->second);
                continue;
            }

            const unsigned int bufferInd = indToBufferIndMap.size();
            indToBufferIndMap[index] = bufferInd;

            indices.push_back(bufferInd);
            points.push_back(pointAtIndex(mesh, index));
        }
    }
}
