#include "vertex_buffer.hpp"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_id);
    bind();
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::record_data(unsigned int n, const float *buffer) const
{
    glBufferData(GL_ARRAY_BUFFER, n, buffer, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    clear();
}

void VertexBuffer::clear() const
{
    unbind();
    glDeleteBuffers(1, &m_id);
}
