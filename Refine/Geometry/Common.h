#ifndef REFINE_GEOMETRY_COMMON_H
#define REFINE_GEOMETRY_COMMON_H

#include <vector>
#include <glm/vec3.hpp>

namespace Refine::Geometry {

    std::vector<glm::vec3> computeNormals(
            const std::vector<glm::vec3> &vertices,
            const std::vector<int> &vertexIndicesTri);

    std::vector<int> triangulate(
            const std::vector<int> &indices,
            const std::vector<int> &polygonStarts);
}

#endif
