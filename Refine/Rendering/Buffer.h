#ifndef REFINE_RENDERING_COMMON_H
#define REFINE_RENDERING_COMMON_H

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "../Geometry/MeshTri.h"

namespace Refine::Rendering {

    struct Point
    {
        glm::vec3 vertex;
        glm::vec2 texcoord = glm::vec2 { 0.0f };
        glm::vec3 normal = glm::vec3 { 0.0f };
    };

    struct Index
    {
        int vertex;
        int texcoord = -1;
        int normal = -1;
    };

    Index makeIndex(
            const Geometry::MeshTri &mesh,
            const int flatIndex);
    Point pointAtIndex(
            const Geometry::MeshTri &mesh,
            const Index &index);

    bool operator==(
            const Index &lhs,
            const Index &rhs);
    bool operator!=(
            const Index &lhs,
            const Index &rhs);

    bool operator==(
            const Point &lhs,
            const Point &rhs);
    bool operator!=(
            const Point &lhs,
            const Point &rhs);

    class Buffer
    {
    public:
        Buffer(const Geometry::MeshTri &mesh);

        void updateGeometry(
                const std::vector<glm::vec3> &vertices,
                const std::vector<glm::vec3> &normals);

        std::vector<Point> points;
        std::vector<Index> indices;
        std::vector<unsigned int> elements;
    };
}

template<>
struct std::hash<Refine::Rendering::Index>
{
    size_t operator()(const Refine::Rendering::Index &index) const
    {
        return std::hash<int>{}(index.vertex)
               ^ std::hash<int>{}(index.texcoord)
               ^ std::hash<int>{}(index.normal);
    }
};

#endif
