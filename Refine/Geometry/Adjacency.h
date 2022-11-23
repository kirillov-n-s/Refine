#ifndef REFINE_GEOMETRY_ADJACENCY_H
#define REFINE_GEOMETRY_ADJACENCY_H

#include <vector>
#include <array>

namespace Refine::Geometry::Adjacency {

    using Edge = std::array<int, 2>;
    using Dihedral = std::array<int, 4>;

    std::vector<Edge> vertexToVertexAsEdges(
            const std::vector<int> &vertexIndicesTri);

    std::vector<Dihedral> triangleToTriangleAsDihedrals(
            const std::vector<int> &vertexIndicesTri);
}

#endif
