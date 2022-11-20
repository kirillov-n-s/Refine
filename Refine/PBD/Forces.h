#ifndef REFINE_PBD_FORCES_H
#define REFINE_PBD_FORCES_H

#include <vector>
#include <glm/vec3.hpp>

namespace Refine::PBD {

    class Force
    {
    public:
        virtual ~Force() = default;

        virtual void accumulate(
                const std::vector<glm::vec3> &positions,
                std::vector<glm::vec3> &accelerations) = 0;
    };

    class ForceConstant : public Force
    {
    public:
        ForceConstant(const glm::vec3 &vector = glm::vec3(0.0f, -9.8f, 0.0f));

        void accumulate(
                const std::vector<glm::vec3> &positions,
                std::vector<glm::vec3> &accelerations) override;

        glm::vec3 vector;
    };
}

#endif
