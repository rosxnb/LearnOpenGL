#include "vertex_array.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
    bind();
}

void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::set_attribute(unsigned int loc, int n, int stride, int offset) const
{
    glVertexAttribPointer(loc, n, GL_FLOAT, GL_FALSE, stride, (void *)(uintptr_t)offset);
    glEnableVertexAttribArray(loc);
}

VertexArray::~VertexArray()
{
    unbind();
    clear();
}

void VertexArray::clear() const
{
    glDeleteVertexArrays(1, &m_id);
}
