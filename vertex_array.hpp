#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <glad/glad.h>

class VertexArray 
{
    public:
        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;
        VertexArray();

        void bind() const;
        void unbind() const;
        void set_attribute(unsigned int loc, int n, int stride, int offset) const;

        ~VertexArray();

    private:
        unsigned int m_id;

        void clear() const;
};

#endif
