#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include "Constraints.h"

namespace Refine::PBD {

    ConstraintDistance::ConstraintDistance(
            const std::vector<glm::vec3> &restPositions,
            const std::vector<std::pair<int, int>> &edges,
            const float compliance)
        : Constraint(compliance),
          m_restDistances(edges.size()),
          m_edges(edges)
    {
        const int nEdges = edges.size();
        for (int edgeInd = 0; edgeInd < nEdges; ++edgeInd) {

            const std::pair<int, int> &edge = m_edges[edgeInd];
            m_restDistances[edgeInd] = glm::length(restPositions[edge.first] - restPositions[edge.second]);
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

            const auto &[ind1, ind2] = m_edges[edgeInd];
            const float restDistance = m_restDistances[edgeInd];

            assert(ind1 >= 0 && ind1 < nPositions);
            assert(ind2 >= 0 && ind2 < nPositions);

            const float w1 = weights[ind1];
            const float w2 = weights[ind2];

            glm::vec3 &x1 = positions[ind1];
            glm::vec3 &x2 = positions[ind2];

            const glm::vec3 edgeVec = x2 - x1;
            const float lambda = (glm::length(edgeVec) - restDistance) / (w1 + w2 + compliance / (dt * dt));
            const glm::vec3 gradient = glm::normalize(edgeVec);
            const glm::vec3 commonMult = lambda * gradient;

            x1 += w1 * commonMult;
            x1 = glm::clamp(x1, min, max);
            x2 += -w2 * commonMult;
            x2 = glm::clamp(x2, min, max);
        }
    }

}
