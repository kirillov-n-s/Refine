#include <unordered_map>
#include "GlBuffer.h"

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

    GlBuffer::GlBuffer(const Geometry::MeshTri &mesh)
    {
        std::unordered_map<Index, unsigned int> indToElemMap;
        const int nFlatIndices = mesh.vertexIndices.size();
        for (int flatInd = 0; flatInd < nFlatIndices; flatInd++) {

            const Index& index = makeIndex(mesh, flatInd);

            const auto &mapPairIt = indToElemMap.find(index);
            if (mapPairIt != indToElemMap.end()) {
                elements.push_back(mapPairIt->second);
                continue;
            }

            const unsigned int elem = indToElemMap.size();
            indToElemMap[index] = elem;

            points.push_back(pointAtIndex(mesh, index));
            indices.push_back(index);
            elements.push_back(elem);
        }
    }

    void GlBuffer::updateGeometry(
            const std::vector<glm::vec3> &vertices,
            const std::vector<glm::vec3> &normals)
    {
        const int nPoints = points.size();
        for (int ind = 0; ind < nPoints; ++ind) {

            const Index &index = indices[ind];
            Point &point = points[ind];

            point.vertex = vertices[index.vertex];
            point.normal = normals[index.normal];
        }
    }
}
