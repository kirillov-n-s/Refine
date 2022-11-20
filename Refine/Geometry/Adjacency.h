#ifndef REFINE_GEOMETRY_ADJACENCY_H
#define REFINE_GEOMETRY_ADJACENCY_H

#include <vector>
#include <utility>

namespace Refine::Geometry::Adjacency {

    std::vector<std::pair<int, int>> vertexToVertexPairsSymmetric(
            const std::vector<int> &vertexIndicesTri);
}

#endif
