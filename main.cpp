#include "shader.hpp"
#include "window.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"

int main()
{
    Window window(1200, 1000);

    // Shader Program
    Shader shader_program("./shaders/vertex.glsl", "./shaders/fragment.glsl");
    shader_program.use();

    // Data and data objects
    constexpr float vertices[] = {
        // positions        // colors         // texture coords
        0.7f,  0.7f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.7f, -0.7f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.7f,  0.7f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };

    constexpr unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;

    vbo.record_data(sizeof(vertices), vertices);
    vao.set_attribute(0, 3, 8 * sizeof(float), 0);
    vao.set_attribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
    vao.set_attribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));
    vbo.unbind();
    ibo.record_indices(sizeof(indices), indices);

    shader_program.set_int("tex_unit0", 0);
    shader_program.set_int("tex_unit1", 1);

    Texture tex0("resources/tree.png", 0);
    tex0.unbind();

    Texture tex1("resources/awesomeface.png", 1);
    tex1.unbind();

    vao.bind();
    ibo.bind();
    tex0.bind();
    tex1.bind();
    while (!window.should_close())
    {
        window.poll_events();
        window.process_input();

        glClearColor(0.f, 0.f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swap_buffers();
    }

    return 0;
}
