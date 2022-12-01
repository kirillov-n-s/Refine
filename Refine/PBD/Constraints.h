#ifndef REFINE_PBD_CONSTRAINTS_H
#define REFINE_PBD_CONSTRAINTS_H

#include <vector>
#include <glm/vec3.hpp>
#include "../Geometry/Adjacency.h"

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
                const std::vector<Geometry::Adjacency::Edge> &edges,
                const float compliance = 0.0f);

        void solve(
                std::vector<glm::vec3> &positions,
                const std::vector<float> &weights,
                const float dt,
                const glm::vec3 &min,
                const glm::vec3 &max) override;

    private:
        std::vector<Geometry::Adjacency::Edge> m_edges;
        std::vector<float> m_restDistances;
    };

    class ConstraintARAP : public Constraint
    {
    public:
        ConstraintARAP(
                const std::vector<glm::vec3> &restPositions,
                const std::vector<Geometry::Adjacency::Edge> &edges,
                const float compliance = 0.0f);

        void solve(
                std::vector<glm::vec3> &positions,
                const std::vector<float> &weights,
                const float dt,
                const glm::vec3 &min,
                const glm::vec3 &max) override;

    private:
        std::vector<Geometry::Adjacency::Edge> m_edges;
        std::vector<glm::vec3> m_restEdgeVectors;
    };

    class ConstraintDihedral : public Constraint
    {
    public:
        ConstraintDihedral(
                const std::vector<glm::vec3> &restPositions,
                const std::vector<Geometry::Adjacency::Dihedral> &dihedrals,
                const float compliance = 0.0f);

        void solve(
                std::vector<glm::vec3> &positions,
                const std::vector<float> &weights,
                const float dt,
                const glm::vec3 &min,
                const glm::vec3 &max) override;

    private:
        std::vector<Geometry::Adjacency::Dihedral> m_dihedrals;
        std::vector<float> m_restAngles;
    };

    class ConstraintDihedralImstk : public Constraint
    {
    public:
        ConstraintDihedralImstk(
                const std::vector<glm::vec3> &restPositions,
                const std::vector<Geometry::Adjacency::Dihedral> &dihedrals,
                const float compliance = 0.0f);

        void solve(
                std::vector<glm::vec3> &positions,
                const std::vector<float> &weights,
                const float dt,
                const glm::vec3 &min,
                const glm::vec3 &max) override;

    private:
        std::vector<Geometry::Adjacency::Dihedral> m_dihedrals;
        std::vector<float> m_restAngles;
    };
}

#endif
