#include "shader.hpp"
#include "window.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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



    // Mathematics setion
    glm::mat4 scale(1.f);
    scale = glm::scale(scale, glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 translate(1.f);
    translate = glm::translate(translate, glm::vec3(0.f, -0.5f, 0.f));

    auto shader_id = shader_program.get_id();
    auto transform_loc = glGetUniformLocation(shader_id, "transform");


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

        glm::mat4 rotate(1.f);
        rotate = glm::rotate(rotate, static_cast<float>(glfwGetTime()), glm::vec3(0.f, 0.f, 1.f));
        glm::mat4 transform = translate * rotate * scale;
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swap_buffers();
    }

    return 0;
}
