#ifndef REFINE_PBD_CONSTRAINTS_H
#define REFINE_PBD_CONSTRAINTS_H

#include <vector>
#include <glm/vec3.hpp>

namespace Refine::PBD {

    class Constraint
    {
    public:
        virtual ~Constraint() = default;

        virtual void solve(
                const std::vector<float> &weights,
                std::vector<glm::vec3> &positions) = 0;
    };

    class ConstraintBox : public Constraint
    {
    public:
        ConstraintBox(const glm::vec3 &min, const glm::vec3 &max);

        void solve(
                const std::vector<float> &weights,
                std::vector<glm::vec3> &positions) override;

        glm::vec3 min;
        glm::vec3 max;
    };

    class ConstraintDistance : public Constraint
    {
    public:
        ConstraintDistance(
                const std::vector<glm::vec3> &restPositions,
                const std::vector<std::pair<int, int>> &edges);

        void solve(
                const std::vector<float> &weights,
                std::vector<glm::vec3> &positions) override;

    private:
        std::vector<std::pair<int, int>> m_edges;
        std::vector<float> m_restDistances;
    };
}

#endif
