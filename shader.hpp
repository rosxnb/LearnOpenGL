#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader 
{
    public:
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader(Shader&&) = delete;
        Shader& operator=(Shader&&) = delete;
        Shader(const char *path_vertex, const char *path_fragment);

        unsigned int get_id() const;
        void use() const;

        int locate_uniform(const char *name) const;
        void set_bool(const char *name, bool value) const;
        void set_int(const char *name, int value) const;
        void set_float(const char *name, float value) const;

        ~Shader();


    private:
        unsigned int m_id;

        bool validate_uniform(int location) const;
        std::string read_file(const char *filepath) const;
        unsigned int prepare_shader(GLenum shader_type, const char *code) const;
        void print_error(unsigned int id, GLenum type, bool shader = true) const;
};

#endif
