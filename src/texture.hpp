#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "glad/glad.h"
#include "stb_image.hpp"

class Texture 
{
    public:
        explicit Texture(const char *path, unsigned int slot = 0, int channel = 4);

        void bind() const;
        void unbind() const;
        void clear() const;

        void set_wrap(GLenum S = GL_REPEAT, GLenum T = GL_REPEAT) const;
        void set_filter(GLenum min_filter = GL_LINEAR_MIPMAP_LINEAR, GLenum mag_filter = GL_LINEAR) const;

        ~Texture();

    private:
        unsigned int m_slot;
        int m_width, m_height, m_BPP;
        unsigned char *m_buffer;
        unsigned int m_id, m_channel;
};

#endif
