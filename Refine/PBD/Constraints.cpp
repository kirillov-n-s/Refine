#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include "Constraints.h"

namespace Refine::PBD {

    ConstraintBox::ConstraintBox(const glm::vec3 &min, const glm::vec3 &max)
        : min(min),
          max(max)
    {}

    void ConstraintBox::solve(
            const std::vector<float> &weights,
            std::vector<glm::vec3> &positions)
    {
        for (glm::vec3 &position : positions)
            position = glm::clamp(position, min, max);
    }

    ConstraintDistance::ConstraintDistance(
            const std::vector<glm::vec3> &restPositions,
            const std::vector<std::pair<int, int>> &edges)
        : m_restDistances(edges.size()),
          m_edges(edges)
    {
        const int nEdges = edges.size();
        for (int edgeInd = 0; edgeInd < nEdges; ++edgeInd) {

            const std::pair<int, int> &edge = m_edges[edgeInd];
            m_restDistances[edgeInd] = glm::length(restPositions[edge.first] - restPositions[edge.second]);
        }
    }

    void ConstraintDistance::solve(
            const std::vector<float> &weights,
            std::vector<glm::vec3> &positions)
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

            const glm::vec3 &x1 = positions[ind1];
            const glm::vec3 &x2 = positions[ind2];

            const glm::vec3 edgeVec = x2 - x1;
            const float distance = glm::length(edgeVec);

            const glm::vec3 common = (distance - restDistance) * glm::normalize(edgeVec) / (w1 + w2);

            positions[ind1] += w1 * common;
            positions[ind2] += -w2 * common;
        }
    }

}
