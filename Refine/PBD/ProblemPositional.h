#ifndef REFINE_PBD_PROBLEMPOSITIONAL_H
#define REFINE_PBD_PROBLEMPOSITIONAL_H

#include "Forces.h"
#include "Constraints.h"

namespace Refine::PBD {

    class ProblemPositional
    {
    public:
        ProblemPositional(
                const std::vector<glm::vec3> &positions,
                const std::vector<float> &masses,
                const int nSubsteps = 10,
                const int nIters = 1);
        ~ProblemPositional();

        int nElements() const;

        void addForce(Force *force);
        void addConstraint(Constraint *constraint);

        std::vector<glm::vec3> solveForPositions(const float dt);

        int nSubsteps;
        int nIters;

    private:
        std::vector<glm::vec3> m_positions;
        std::vector<glm::vec3> m_prevPositions;
        std::vector<glm::vec3> m_velocities;

        std::vector<float> m_weights;

        std::vector<Force *> m_forces;
        std::vector<Constraint *> m_constraints;

        void integrate(const float dt);
        void solveConstraints();
        void updateVelocities(const float dt);
    };
}


#endif
