#ifndef REFINE_RENDERING_GLMESH_H
#define REFINE_RENDERING_GLMESH_H

#include "Common.h"

namespace Refine::Rendering {

    class GlMesh
    {
    public:
        GlMesh(
                const std::vector<Point> &points,
                const std::vector<unsigned int> &indices);
        ~GlMesh();

        void draw() const;

        void updateGeometry(const std::vector<Point> &newPoints);

    private:
        int m_nElements;

        unsigned int m_vertexBufferObject;
        unsigned int m_vertexArrayObject;
        unsigned int m_elementBufferObject;
    };
}

#endif
