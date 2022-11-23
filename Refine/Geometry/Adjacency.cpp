#include <cassert>
#include <set>
#include <map>
#include "Adjacency.h"

namespace Refine::Geometry::Adjacency {

    std::vector<Edge> vertexToVertexAsEdges(
            const std::vector<int> &vertexIndicesTri)
    {
        assert(vertexIndicesTri.size() % 3 == 0);

        std::set<Edge> edges;

        const int nTriangles = vertexIndicesTri.size() / 3;
        for (int triangleInd = 0; triangleInd < nTriangles; ++triangleInd) {

            const int a = vertexIndicesTri[triangleInd * 3 + 0];
            const int b = vertexIndicesTri[triangleInd * 3 + 1];
            const int c = vertexIndicesTri[triangleInd * 3 + 2];

            assert(a != b);
            assert(a != c);
            assert(b != c);

            edges.insert(a < b ? Edge {a, b} : Edge {b, a});
            edges.insert(a < c ? Edge {a, c} : Edge {c, a});
            edges.insert(b < c ? Edge {b, c} : Edge {c, b});
        }

        return {edges.begin(), edges.end()};
    }

    std::vector<Dihedral> triangleToTriangleAsDihedrals(
            const std::vector<int> &vertexIndicesTri)
    {
        assert(vertexIndicesTri.size() % 3 == 0);

        std::vector<Dihedral> dihedrals;
        std::map<Edge, Dihedral> edgesToDihedralsMap;

        const int nTriangles = vertexIndicesTri.size() / 3;
        for (int triangleInd = 0; triangleInd < nTriangles; ++triangleInd) {

            const int a = vertexIndicesTri[triangleInd * 3 + 0];
            const int b = vertexIndicesTri[triangleInd * 3 + 1];
            const int c = vertexIndicesTri[triangleInd * 3 + 2];

            assert(a != b);
            assert(a != c);
            assert(b != c);

            const Edge ab = a < b ? Edge {a, b} : Edge {b, a};
            const auto &abIt = edgesToDihedralsMap.find(ab);
            if (abIt == edgesToDihedralsMap.end())
                edgesToDihedralsMap[ab] = {c, -1, a, b};
            else {
                Dihedral dihedral = abIt->second;
                dihedral[1] = c;
                dihedrals.push_back(dihedral);
                edgesToDihedralsMap.erase(abIt);
            }

            const Edge bc = b < c ? Edge {b, c} : Edge {c, b};
            const auto &bcIt = edgesToDihedralsMap.find(bc);
            if (bcIt == edgesToDihedralsMap.end())
                edgesToDihedralsMap[bc] = {a, -1, b, c};
            else {
                Dihedral dihedral = bcIt->second;
                dihedral[1] = a;
                dihedrals.push_back(dihedral);
                edgesToDihedralsMap.erase(bcIt);
            }

            const Edge ca = c < a ? Edge {c, a} : Edge {a, c};
            const auto &caIt = edgesToDihedralsMap.find(ca);
            if (caIt == edgesToDihedralsMap.end())
                edgesToDihedralsMap[ca] = {b, -1, c, a};
            else {
                Dihedral dihedral = caIt->second;
                dihedral[1] = b;
                dihedrals.push_back(dihedral);
                edgesToDihedralsMap.erase(caIt);
            }
        }

        return dihedrals;
    }
}
