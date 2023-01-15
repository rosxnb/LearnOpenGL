#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <glad/glad.h>

class IndexBuffer 
{
    public:
        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;
        IndexBuffer();

        void bind() const;
        void unbind() const;
        void record_indices(unsigned int size, const unsigned int *buffer) const;

        ~IndexBuffer();

    private:
        unsigned int m_id;

        void clear() const;
};

#endif
