# include "shader.hpp"

Shader::Shader(const char *path_vertex, const char *path_fragment)
{
    std::string code_vertex = read_file(path_vertex);
    std::string code_fragment = read_file(path_fragment);

    unsigned int vertex_shader = prepare_shader(GL_VERTEX_SHADER, code_vertex.c_str());
    unsigned int fragment_shader = prepare_shader(GL_FRAGMENT_SHADER, code_fragment.c_str());

    m_id = glCreateProgram();
    glAttachShader(m_id, vertex_shader);
    glAttachShader(m_id, fragment_shader);
    glLinkProgram(m_id);
    print_error(m_id, GL_LINK_STATUS, false);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

unsigned int Shader::get_id() const
{
    return m_id;
}

void Shader::use() const
{
    glUseProgram(m_id);
}

int Shader::locate_uniform(const char *name) const
{
    return glGetUniformLocation(m_id, name);
}

void Shader::set_bool(const char *name, bool value) const
{
    int loc = locate_uniform(name);
    if (loc == -1)
    {
        std::cout << "ERROR uniform: " << name << ", couldn't be found! \n";
        return;
    }
    glUniform1i(loc, static_cast<int>(value));
}

void Shader::set_int(const char *name, int value) const
{
    int loc = locate_uniform(name);
    if (loc == -1)
    {
        std::cout << "ERROR uniform: " << name << ", couldn't be found! \n";
        return;
    }
    glUniform1i(loc, value);
}

void Shader::set_float(const char *name, float value) const
{
    int loc = locate_uniform(name);
    if (loc == -1)
    {
        std::cout << "ERROR uniform: " << name << ", couldn't be found! \n";
        return;
    }
    glUniform1f(loc, value);
}

Shader::~Shader()
{
    glUseProgram(0);
    glDeleteProgram(m_id);
}

bool Shader::validate_uniform(int location) const
{
    return location != -1;
}

std::string Shader::read_file(const char *filepath) const
{
    std::string buffer {};

    std::ifstream file;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try 
    {
        std::stringstream streams;
        file.open(filepath);
        streams << file.rdbuf();
        buffer = streams.str();
    }
    catch (std::ifstream::failure err)
    {
        std::cout << "ERROR: File couldn't be read properly \n location passed: " 
            << filepath << "\n error message: \n" << err.what() << "\n";
    }

    return buffer;
}

unsigned int Shader::prepare_shader(GLenum shader_type, const char *code) const
{
    unsigned int id = glCreateShader(shader_type);
    glShaderSource(id, 1, &code, nullptr);
    glCompileShader(id);
    print_error(id, GL_COMPILE_STATUS);
    return id;
}

void Shader::print_error(unsigned int id, GLenum type, bool shader) const
{
    int sucess_status;
    char infoLog[1024];

    if (shader)
    {
        glGetShaderiv(id, type, &sucess_status);
        if (!sucess_status)
        {
            glGetShaderInfoLog(id, 1024, nullptr, infoLog);
            std::string shader_type = (type == GL_VERTEX_SHADER) ? 
                "VERTEX SHADER" : "FRAGMENT SHADER";
            std::cout << shader_type << " ERROR: \n" << infoLog << "\n"; 
        }
        return;
    }

    glGetProgramiv(id, type, &sucess_status);
    if (!sucess_status)
    {
        glGetProgramInfoLog(id, 1024, nullptr, infoLog);
        std::cout << "SHADER PROGRAM ERROR: \n" << infoLog << "\n";
    }
}
