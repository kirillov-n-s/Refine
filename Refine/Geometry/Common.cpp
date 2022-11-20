#include <glm/geometric.hpp>
#include "../Common/Common.h"
#include "Common.h"

namespace Refine::Geometry {

    std::vector<glm::vec3> computeNormals(
            const std::vector<glm::vec3> &vertices,
            const std::vector<int> &vertexIndicesTri)
    {
        assert(vertexIndicesTri.size() % 3 == 0);

        const int nVertices = vertices.size();
        std::vector<glm::vec3> normals(nVertices, glm::vec3(0.0f));
        std::vector<int> nTrianglesByVertex(nVertices, 0);

        const int nTriangles = vertexIndicesTri.size() / 3;
        for (int triangleInd = 0; triangleInd < nTriangles; ++triangleInd) {

            const int aInd = triangleInd * 3 + 0;
            const int bInd = triangleInd * 3 + 1;
            const int cInd = triangleInd * 3 + 2;

            assert(aInd != bInd);
            assert(aInd != cInd);
            assert(bInd != cInd);

            ++nTrianglesByVertex[aInd];
            ++nTrianglesByVertex[bInd];
            ++nTrianglesByVertex[cInd];

            const glm::vec3 &a = vertices[aInd];
            const glm::vec3 &b = vertices[bInd];
            const glm::vec3 &c = vertices[cInd];

            const glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));

            normals[aInd] += normal;
            normals[bInd] += normal;
            normals[cInd] += normal;
        }

        for (int vertexInd = 0; vertexInd < nVertices; ++vertexInd) {

            assert(nTrianglesByVertex[vertexInd] != 0);
            normals[vertexInd] /= nTrianglesByVertex[vertexInd];
            assert(Common::fuzzyCompare(glm::length(normals[vertexInd]), 1.0f));
        }

        return normals;
    }

    std::vector<int> triangulate(
            const std::vector<int> &indices,
            const std::vector<int> &polygonStarts)
    {
        std::vector<int> indicesTri;
        indicesTri.reserve(indices.size());

        const int nPolygons = polygonStarts.size();
        for (int polygonInd = 0; polygonInd < nPolygons; ++polygonInd) {

            const int faceBegin = polygonStarts[polygonInd];
            const int faceEnd = polygonStarts[polygonInd + 1];
            for (int faceInd = faceBegin + 1; faceInd < faceEnd; ++faceInd) {

                indicesTri.push_back(indices[faceBegin]);
                indicesTri.push_back(indices[faceInd]);
                indicesTri.push_back(indices[faceInd + 1]);
            }
        }

        return indicesTri;
    }
}
