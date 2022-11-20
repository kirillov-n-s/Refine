#include "Forces.h"

namespace Refine::PBD {

    ForceConstant::ForceConstant(const glm::vec3 &vector)
        : vector(vector)
    {}

    void ForceConstant::accumulate(
            const std::vector<glm::vec3> &positions,
            std::vector<glm::vec3> &accelerations)
    {
        for (glm::vec3 &acceleration : accelerations)
            acceleration += vector;
    }
}
