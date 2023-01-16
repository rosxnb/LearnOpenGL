#include "texture.hpp"

Texture::Texture(const char *path, unsigned int slot, int channel)
    : m_slot(slot), m_width(0), m_height(0), m_BPP(0), m_buffer(nullptr), m_channel(channel)
{
    stbi_set_flip_vertically_on_load(true);
    m_buffer = stbi_load(path, &m_width, &m_height, &m_BPP, m_channel);

    glGenTextures(1, &m_id);
    bind();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    set_wrap();
    set_filter();

    if (m_buffer)
        stbi_image_free(m_buffer);
}

void Texture::bind() const
{
    glActiveTexture(GL_TEXTURE0 + m_slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::clear() const
{
    glDeleteTextures(1, &m_id);
}

void Texture::set_wrap(GLenum S, GLenum T) const
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, T);
}

void Texture::set_filter(GLenum min_filter, GLenum mag_filter) const
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
}

Texture::~Texture()
{
    unbind();
    clear();
}
