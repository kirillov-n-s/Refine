#ifndef REFINE_RENDERING_GLMESH_H
#define REFINE_RENDERING_GLMESH_H

#include "GlBuffer.h"

namespace Refine::Rendering {

    class GlMesh
    {
    public:
        GlMesh(const GlBuffer &buffer);
        ~GlMesh();

        void draw() const;

        void swapVertexBuffer(const GlBuffer &buffer) const;

    private:
        int m_nElements;

        unsigned int m_vertexBufferObject;
        unsigned int m_vertexArrayObject;
        unsigned int m_elementBufferObject;
    };
}

#endif
