#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/norm.hpp>
#include "../Common/Common.h"
#include "Constraints.h"

namespace Refine::PBD {

    ConstraintDistance::ConstraintDistance(
            const std::vector<glm::vec3> &restPositions,
            const std::vector<Geometry::Adjacency::Edge> &edges,
            const float compliance)
        : Constraint(compliance),
          m_restDistances(edges.size()),
          m_edges(edges)
    {
        const int nEdges = edges.size();
        for (int edgeInd = 0; edgeInd < nEdges; ++edgeInd) {

            const Geometry::Adjacency::Edge &edge = m_edges[edgeInd];
            m_restDistances[edgeInd] = glm::length(restPositions[edge[0]] - restPositions[edge[1]]);
        }
    }

    void ConstraintDistance::solve(
            std::vector<glm::vec3> &positions,
            const std::vector<float> &weights,
            const float dt,
            const glm::vec3 &min,
            const glm::vec3 &max)
    {
        const int nPositions = positions.size();
        const int nEdges = m_edges.size();
        for (int edgeInd = 0; edgeInd < nEdges; ++edgeInd) {

            const Geometry::Adjacency::Edge &edge = m_edges[edgeInd];
            const float restDistance = m_restDistances[edgeInd];

            const int i1 = edge[0];
            const int i2 = edge[1];

            assert(i1 >= 0 && i1 < nPositions);
            assert(i2 >= 0 && i2 < nPositions);

            glm::vec3 &x1 = positions[i1];
            glm::vec3 &x2 = positions[i2];

            const glm::vec3 edgeVec = x2 - x1;
            const float edgeLen = glm::length(edgeVec);

            const float w1 = weights[i1];
            const float w2 = weights[i2];

            const float lambda = (edgeLen - restDistance) / (w1 + w2 + compliance / (dt * dt));
            const glm::vec3 gradient = edgeVec / edgeLen;
            const glm::vec3 tmp = lambda * gradient;

            x1 += w1 * tmp;
            x1 = glm::clamp(x1, min, max);
            x2 += -w2 * tmp;
            x2 = glm::clamp(x2, min, max);
        }
    }

    ConstraintARAP::ConstraintARAP(
            const std::vector<glm::vec3> &restPositions,
            const std::vector<Geometry::Adjacency::Edge> &edges,
            const float compliance)
        : Constraint(compliance),
          m_restEdgeVectors(edges.size()),
          m_edges(edges)
    {
        const int nEdges = edges.size();
        for (int edgeInd = 0; edgeInd < nEdges; ++edgeInd) {

            const Geometry::Adjacency::Edge &edge = m_edges[edgeInd];
            m_restEdgeVectors[edgeInd] = restPositions[edge[1]] - restPositions[edge[0]];
        }
    }

    void ConstraintARAP::solve(
            std::vector<glm::vec3> &positions,
            const std::vector<float> &weights,
            const float dt,
            const glm::vec3 &min,
            const glm::vec3 &max)
    {
        const int nPositions = positions.size();
        const int nEdges = m_edges.size();
        for (int edgeInd = 0; edgeInd < nEdges; ++edgeInd) {

            const Geometry::Adjacency::Edge &edge = m_edges[edgeInd];
            const glm::vec3 &restEdgeVec = m_restEdgeVectors[edgeInd];

            const int i1 = edge[0];
            const int i2 = edge[1];

            assert(i1 >= 0 && i1 < nPositions);
            assert(i2 >= 0 && i2 < nPositions);

            glm::vec3 &x1 = positions[i1];
            glm::vec3 &x2 = positions[i2];

            const glm::vec3 edgeVec = x2 - x1;

            const float w1 = weights[i1];
            const float w2 = weights[i2];

            const glm::vec3 tmp = (edgeVec - restEdgeVec) / (w1 + w2 + compliance / (dt * dt));

            x1 += w1 * tmp;
            x1 = glm::clamp(x1, min, max);
            x2 += -w2 * tmp;
            x2 = glm::clamp(x2, min, max);
        }
    }

    ConstraintDihedral::ConstraintDihedral(
            const std::vector<glm::vec3> &restPositions,
            const std::vector<Geometry::Adjacency::Dihedral> &dihedrals,
            const float compliance)
        : Constraint(compliance),
          m_dihedrals(dihedrals),
          m_restAngles(dihedrals.size())
    {
        const int nDihedrals = dihedrals.size();
        for (int dihedralInd = 0; dihedralInd < nDihedrals; ++dihedralInd) {

            const Geometry::Adjacency::Dihedral &dihedral = m_dihedrals[dihedralInd];

            const glm::vec3 &p0 = restPositions[dihedral[0]];
            const glm::vec3 &p1 = restPositions[dihedral[1]];
            const glm::vec3 &p2 = restPositions[dihedral[2]];
            const glm::vec3 &p3 = restPositions[dihedral[3]];

            const glm::vec3 n1 = glm::normalize(glm::cross(p3 - p2, p0 - p2));
            const glm::vec3 n2 = glm::normalize(glm::cross(p3 - p2, p1 - p2));

            m_restAngles[dihedralInd] = std::acos(glm::dot(n1, n2));
        }
    }

    void ConstraintDihedral::solve(
            std::vector<glm::vec3> &positions,
            const std::vector<float> &weights,
            const float dt,
            const glm::vec3 &min,
            const glm::vec3 &max)
    {
        const int nPositions = positions.size();
        const int nDihedrals = m_dihedrals.size();
        for (int dihedralInd = 0; dihedralInd < nDihedrals; ++dihedralInd) {

            const Geometry::Adjacency::Dihedral &dihedral = m_dihedrals[dihedralInd];
            const float restAngle = m_restAngles[dihedralInd];

            const int i0 = dihedral[0];
            const int i1 = dihedral[1];
            const int i2 = dihedral[2];
            const int i3 = dihedral[3];

            assert(i0 >= 0 && i0 < nPositions);
            assert(i1 >= 0 && i1 < nPositions);
            assert(i2 >= 0 && i2 < nPositions);
            assert(i3 >= 0 && i3 < nPositions);

            glm::vec3 &p0 = positions[i0];
            glm::vec3 &p1 = positions[i1];
            glm::vec3 &p2 = positions[i2];
            glm::vec3 &p3 = positions[i3];

            const glm::vec3 n1 = glm::normalize(glm::cross(p3, p0));
            const glm::vec3 n2 = glm::normalize(glm::cross(p3, p1));

            const float d = glm::dot(n1, n2);

            const glm::vec3 p3n1 = glm::cross(p3, n1);
            const glm::vec3 p3n2 = glm::cross(p3, n2);
            const glm::vec3 p0n2 = glm::cross(p0, n2);
            const glm::vec3 n1p0 = glm::cross(n1, p0);
            const glm::vec3 p1n1 = glm::cross(p1, n1);
            const glm::vec3 n2p1 = glm::cross(n2, p1);

            const float p3p0_l = glm::length(glm::cross(p3, p0));
            const float p3p1_l = glm::length(glm::cross(p3, p1));

            const glm::vec3 q0 = (p3n2 - p3n1 * d) / p3p0_l;
            const glm::vec3 q1 = (p3n1 - p3n2 * d) / p3p1_l;
            const glm::vec3 q3 = -(p0n2 + n1p0 * d) / p3p0_l - (p1n1 + n2p1 * d) / p3p1_l;
            const glm::vec3 q2 = -q0 - q1 - q3;

            const float w0 = weights[i0];
            const float w1 = weights[i1];
            const float w2 = weights[i2];
            const float w3 = weights[i3];

            const float q0_l2 = glm::length2(q0);
            const float q1_l2 = glm::length2(q1);
            const float q2_l2 = glm::length2(q2);
            const float q3_l2 = glm::length2(q3);

            const float c = std::acos(d) - restAngle;
            const float lambda = -c * std::sqrt(1.0f - d * d)
                    / (w0 * q0_l2 + w1 * q1_l2 + w2 * q2_l2 + w3 * q3_l2 + compliance / (dt * dt));

            p0 += lambda * w0 * q0;
            p0 = glm::clamp(p0, min, max);
            p1 += lambda * w1 * q1;
            p1 = glm::clamp(p1, min, max);
            p2 += lambda * w2 * q2;
            p2 = glm::clamp(p2, min, max);
            p3 += lambda * w3 * q3;
            p3 = glm::clamp(p3, min, max);
        }
    }

    ConstraintDihedralImstk::ConstraintDihedralImstk(
            const std::vector<glm::vec3> &restPositions,
            const std::vector<Geometry::Adjacency::Dihedral> &dihedrals,
            const float compliance)
        : Constraint(compliance),
          m_dihedrals(dihedrals),
          m_restAngles(dihedrals.size())
    {
        const int nDihedrals = dihedrals.size();
        for (int dihedralInd = 0; dihedralInd < nDihedrals; ++dihedralInd) {

            const Geometry::Adjacency::Dihedral &dihedral = m_dihedrals[dihedralInd];

            const glm::vec3 &p0 = restPositions[dihedral[0]];
            const glm::vec3 &p1 = restPositions[dihedral[1]];
            const glm::vec3 &p2 = restPositions[dihedral[2]];
            const glm::vec3 &p3 = restPositions[dihedral[3]];

            const glm::vec3 n1 = glm::normalize(glm::cross(p2 - p0, p3 - p0));
            const glm::vec3 n2 = glm::normalize(glm::cross(p3 - p1, p2 - p1));

            m_restAngles[dihedralInd] = std::atan2(
                    glm::dot(glm::cross(n1, n2), p3 - p2),
                    glm::length(p3 - p2) * glm::dot(n1, n2));
        }
    }

    void ConstraintDihedralImstk::solve(
            std::vector<glm::vec3> &positions,
            const std::vector<float> &weights,
            const float dt,
            const glm::vec3 &min,
            const glm::vec3 &max)
    {
        const int nPositions = positions.size();
        const int nDihedrals = m_dihedrals.size();
        for (int dihedralInd = 0; dihedralInd < nDihedrals; ++dihedralInd) {

            const Geometry::Adjacency::Dihedral &dihedral = m_dihedrals[dihedralInd];
            const float restAngle = m_restAngles[dihedralInd];

            const int i0 = dihedral[0];
            const int i1 = dihedral[1];
            const int i2 = dihedral[2];
            const int i3 = dihedral[3];

            assert(i0 >= 0 && i0 < nPositions);
            assert(i1 >= 0 && i1 < nPositions);
            assert(i2 >= 0 && i2 < nPositions);
            assert(i3 >= 0 && i3 < nPositions);

            glm::vec3 &p0 = positions[i0];
            glm::vec3 &p1 = positions[i1];
            glm::vec3 &p2 = positions[i2];
            glm::vec3 &p3 = positions[i3];

            const glm::vec3 e = p3 - p2;
            const glm::vec3 e1 = p3 - p0;
            const glm::vec3 e2 = p0 - p2;
            const glm::vec3 e3 = p3 - p1;
            const glm::vec3 e4 = p1 - p2;

            const float l = glm::length(e);
            if (Common::fuzzyIsNull(l))
                continue;

            glm::vec3 n1 = glm::cross(e1, e);
            glm::vec3 n2 = glm::cross(e, e3);
            const float a1 = glm::length(n1);
            const float a2 = glm::length(n2);
            n1 /= a1;
            n2 /= a2;

            const glm::vec3 tmp1 = n1 / (a1 * l);
            const glm::vec3 tmp2 = n2 / (a2 * l);

            const glm::vec3 dc0 = -(l / a1) * n1;
            const glm::vec3 dc1 = -(l / a2) * n2;
            const glm::vec3 dc2 = glm::dot(e, e1) * tmp1 + glm::dot(e, e3) * tmp2;
            const glm::vec3 dc3 = glm::dot(e, e2) * tmp1 + glm::dot(e, e4) * tmp2;

            const float c = std::atan2(glm::dot(glm::cross(n1, n2), e), l * glm::dot(n1, n2)) - restAngle;

            const float w0 = weights[i0];
            const float w1 = weights[i1];
            const float w2 = weights[i2];
            const float w3 = weights[i3];

            const float dc0_l2 = glm::length2(dc0);
            const float dc1_l2 = glm::length2(dc1);
            const float dc2_l2 = glm::length2(dc2);
            const float dc3_l2 = glm::length2(dc3);

            const float lambda = -c / (w0 * dc0_l2 + w1 * dc1_l2 + w2 * dc2_l2 + w3 * dc3_l2 + compliance / (dt * dt));

            p0 += lambda * w0 * dc0;
            p0 = glm::clamp(p0, min, max);
            p1 += lambda * w1 * dc1;
            p1 = glm::clamp(p1, min, max);
            p2 += lambda * w2 * dc2;
            p2 = glm::clamp(p2, min, max);
            p3 += lambda * w3 * dc3;
            p3 = glm::clamp(p3, min, max);
        }
    }
}
