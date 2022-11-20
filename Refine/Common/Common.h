#ifndef REFINE_COMMON_COMMON_H
#define REFINE_COMMON_COMMON_H

#ifndef EPSILON_FLOAT
#define EPSILON_FLOAT 1e-5f
#endif

#include <glm/gtc/epsilon.hpp>

namespace Refine::Common {

    template <typename T>
    bool fuzzyIsNull(const T &x)
    {
        if constexpr (std::is_same_v<T, float>)
            return std::abs(x) <= EPSILON_FLOAT;
        else
            return glm::all(glm::epsilonEqual(x, T(0), EPSILON_FLOAT));
    }

    template <typename T>
    bool fuzzyCompare(const T &x, const T &y)
    {
        if constexpr (std::is_same_v<T, float>)
            return std::abs(x - y) <= EPSILON_FLOAT;
        else
            return glm::all(glm::epsilonEqual(x, y, EPSILON_FLOAT));
    }
}

#endif
