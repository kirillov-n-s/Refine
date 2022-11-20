#include <vector>
#include <GL/glew.h>
#include "GlMesh.h"

namespace Refine::Rendering {

    GlMesh::GlMesh(
            const std::vector<Point> &points,
            const std::vector<unsigned int> &indices)
        : m_nElements(indices.size())
    {
        glGenVertexArrays(1, &m_vertexArrayObject);
        glBindVertexArray(m_vertexArrayObject);

        glGenBuffers(1, &m_vertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
        glBufferData(
            GL_ARRAY_BUFFER,
            points.size() * sizeof(Point),
            points.data(),
            GL_STATIC_DRAW);

        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Point),
            nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Point),
            (void*)offsetof(Point, texcoord));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            2,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Point),
            (void*)offsetof(Point, normal));
        glEnableVertexAttribArray(2);

        glGenBuffers(1, &m_elementBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                m_nElements * sizeof(unsigned int),
                indices.data(),
                GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    GlMesh::~GlMesh()
    {
        glDeleteVertexArrays(1, &m_vertexArrayObject);
        glDeleteBuffers(1, &m_vertexBufferObject);
        glDeleteBuffers(1, &m_elementBufferObject);
    }

    void GlMesh::draw() const
    {
        glBindVertexArray(m_vertexArrayObject);
        glDrawElements(
                GL_TRIANGLES,
                m_nElements,
                GL_UNSIGNED_INT,
                nullptr);
        glBindVertexArray(0);
    }

    void GlMesh::updateGeometry(const std::vector<Point> &newPoints)
    {
        glBindVertexArray(m_vertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
        glBufferData(
                GL_ARRAY_BUFFER,
                newPoints.size() * sizeof(Point),
                newPoints.data(),
                GL_STATIC_DRAW);
    }
}
