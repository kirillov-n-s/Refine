#ifndef REFINE_PBD_CONSTRAINTS_H
#define REFINE_PBD_CONSTRAINTS_H

#include <vector>
#include <glm/vec3.hpp>

namespace Refine::PBD {

    class Constraint
    {
    public:
        Constraint(const float compliance)
            : compliance(compliance)
        {}

        virtual ~Constraint() = default;

        virtual void solve(
                std::vector<glm::vec3> &positions,
                const std::vector<float> &weights,
                const float dt,
                const glm::vec3 &min,
                const glm::vec3 &max) = 0;

        float compliance = 0.0f;
    };

    class ConstraintDistance : public Constraint
    {
    public:
        ConstraintDistance(
                const std::vector<glm::vec3> &restPositions,
                const std::vector<std::pair<int, int>> &edges,
                const float compliance = 0.0f);

        void solve(
                std::vector<glm::vec3> &positions,
                const std::vector<float> &weights,
                const float dt,
                const glm::vec3 &min,
                const glm::vec3 &max) override;

    private:
        std::vector<std::pair<int, int>> m_edges;
        std::vector<float> m_restDistances;
    };
}

#endif
