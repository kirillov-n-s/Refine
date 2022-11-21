#ifndef REFINE_PBD_PROBLEMPOSITIONAL_H
#define REFINE_PBD_PROBLEMPOSITIONAL_H

#include "../Spatial/AABB.h"
#include "Forces.h"
#include "Constraints.h"

namespace Refine::PBD {

    class ProblemPositional
    {
    public:
        ProblemPositional(
                const std::vector<glm::vec3> &positions,
                const std::vector<float> &weights,
                const Spatial::AABB &aabb = { .min = glm::vec3(-1e6), .max = glm::vec3(1e6) },
                const int nSubsteps = 10,
                const int nIters = 1);
        ~ProblemPositional();

        int nElements() const;

        void addForce(Force *force);
        void addConstraint(Constraint *constraint);

        std::vector<glm::vec3> solveForPositions(const float dt);

        Spatial::AABB aabb;
        int nSubsteps = 0;
        int nIters = 0;

    private:
        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_prevPositions;
        std::vector<glm::vec3> m_velocities;

        std::vector<float> m_weights;

        std::vector<Force *> m_forces;
        std::vector<Constraint *> m_constraints;

        void integrate(const float dt);
        void solveConstraints(const float dt);
        void updateVelocities(const float dt);
    };
}


#endif
