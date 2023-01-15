#include "index_buffer.hpp"

IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &m_id);
    bind();
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::record_indices(unsigned int n, const unsigned int *buffer) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, n, buffer, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    clear();
}

void IndexBuffer::clear() const
{
    unbind();
    glDeleteBuffers(1, &m_id);
}
