#ifndef REFINE_RENDERING_GLMESH_H
#define REFINE_RENDERING_GLMESH_H

#include "Buffer.h"

namespace Refine::Rendering {

    class GlMesh
    {
    public:
        GlMesh(const Buffer &buffer);
        ~GlMesh();

        void draw() const;

        void swapVertexBuffer(const Buffer &buffer) const;

    private:
        int m_nElements;

        unsigned int m_vertexBufferObject;
        unsigned int m_vertexArrayObject;
        unsigned int m_elementBufferObject;
    };
}

#endif
