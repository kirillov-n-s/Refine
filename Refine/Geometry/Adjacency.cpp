#include <cassert>
#include <set>
#include "Adjacency.h"

namespace Refine::Geometry::Adjacency {

    std::vector<std::pair<int, int>> vertexToVertexPairsSymmetric(
            const std::vector<int> &vertexIndicesTri)
    {
        assert(vertexIndicesTri.size() % 3 == 0);

        std::set<std::pair<int, int>> edgesSet;

        const int nTriangles = vertexIndicesTri.size() / 3;
        for (int triangleInd = 0; triangleInd < nTriangles; ++triangleInd) {

            const int aInd = triangleInd * 3 + 0;
            const int bInd = triangleInd * 3 + 1;
            const int cInd = triangleInd * 3 + 2;

            assert(aInd != bInd);
            assert(aInd != cInd);
            assert(bInd != cInd);

            edgesSet.insert(aInd < bInd ? std::make_pair(aInd, bInd) : std::make_pair(bInd, aInd));
            edgesSet.insert(aInd < cInd ? std::make_pair(aInd, cInd) : std::make_pair(cInd, aInd));
            edgesSet.insert(bInd < cInd ? std::make_pair(bInd, cInd) : std::make_pair(cInd, bInd));
        }

        return { edgesSet.begin(), edgesSet.end() };
    }
}
