#ifndef REFINE_SPATIAL_AABB_H
#define REFINE_SPATIAL_AABB_H

#include <glm/vec3.hpp>

namespace Refine::Spatial {

    struct AABB
    {
        glm::vec3 min {-std::numeric_limits<float>::max()};
        glm::vec3 max {std::numeric_limits<float>::max()};
    };
}

#endif
