#include "ProblemPositional.h"

#include <utility>

namespace Refine::PBD {

    ProblemPositional::ProblemPositional(
            const std::vector<glm::vec3> &positions,
            const std::vector<float> &masses,
            const int nSubsteps,
            const int nIters)
    : m_positions(positions),
      m_prevPositions(positions.size()),
      m_velocities(positions.size(), glm::vec3(0.0f)),
      m_weights(masses),
      nSubsteps(nSubsteps),
      nIters(nIters)
    {
        for (float &weight : m_weights)
            weight = 1.0f / weight;
    }

    ProblemPositional::~ProblemPositional()
    {
        for (Force *force : m_forces)
            delete force;
        for (Constraint *constraint : m_constraints)
            delete constraint;
    }

    int ProblemPositional::nElements() const
    {
        return m_positions.size();
    }

    void ProblemPositional::addForce(Force *force)
    {
        m_forces.push_back(force);
    }

    void ProblemPositional::addConstraint(Constraint *constraint)
    {
        m_constraints.push_back(constraint);
    }

    std::vector<glm::vec3> ProblemPositional::solveForPositions(const float dt)
    {
        const float dtSub = dt / nSubsteps;
        for (int substepInd = 0; substepInd < nSubsteps; ++ substepInd) {

            integrate(dtSub);
            solveConstraints();
            updateVelocities(dtSub);
        }
        return m_positions;
    }

    void ProblemPositional::integrate(const float dt)
    {
        std::vector<glm::vec3> accelerations(m_positions.size(), glm::vec3(0.0f));
        for (Force *force : m_forces)
            force->accumulate(m_positions, accelerations);

        const int nElements = this->nElements();
        for (int elemInd = 0; elemInd < nElements; ++elemInd)
            m_velocities[elemInd] += accelerations[elemInd] * dt * m_weights[elemInd];
        m_prevPositions.assign(m_positions.begin(), m_positions.end());
        for (int elemInd = 0; elemInd < nElements; ++elemInd)
            m_positions[elemInd] += m_velocities[elemInd] * dt;
    }

    void ProblemPositional::solveConstraints()
    {
        for (int iter = 0; iter < nIters; ++iter)
            for (Constraint *constraint : m_constraints)
                constraint->solve(m_weights, m_positions);
    }

    void ProblemPositional::updateVelocities(const float dt)
    {
        const int nElements = this->nElements();
        for (int elemInd = 0; elemInd < nElements; ++elemInd)
            m_velocities[elemInd] = (m_positions[elemInd] - m_prevPositions[elemInd]) / dt;
    }
}
