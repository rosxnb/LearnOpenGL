#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <glad/glad.h>

class VertexBuffer 
{
    public:
        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;
        VertexBuffer();

        void bind() const;
        void unbind() const;
        void record_data(unsigned int n, const float *buffer) const;
    
        ~VertexBuffer();

    private:
        unsigned int m_id;

        void clear() const;
};

#endif
