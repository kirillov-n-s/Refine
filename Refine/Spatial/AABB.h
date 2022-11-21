#ifndef REFINE_SPATIAL_AABB_H
#define REFINE_SPATIAL_AABB_H

#include <glm/vec3.hpp>

namespace Refine::Spatial {

    struct AABB
    {
        glm::vec3 min;
        glm::vec3 max;
    };
}

#endif
