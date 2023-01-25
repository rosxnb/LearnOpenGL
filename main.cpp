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
    glEnable(GL_DEPTH_TEST);

    // Shader Program
    Shader shader_program("./shaders/vertex.glsl", "./shaders/fragment.glsl");
    shader_program.use();


    // Data and data objects
    constexpr float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    VertexArray vao;
    VertexBuffer vbo;

    vbo.record_data(sizeof(vertices), vertices);
    vao.set_attribute(0, 3, 5 * sizeof(float), 0);
    vao.set_attribute(1, 2, 5 * sizeof(float), 3 * sizeof(float));
    vbo.unbind();

    shader_program.set_int("tex_unit0", 0);
    shader_program.set_int("tex_unit1", 1);

    Texture tex0("resources/tree.png", 0);
    tex0.unbind();

    Texture tex1("resources/awesomeface.png", 1);
    tex1.unbind();


    glm::mat4 view(1.f);
    view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
    shader_program.set_mat4("view", view);

    glm::mat4 projection(1.f);
    auto [width, height] = window.get_buffer_size();
    projection = glm::perspective(glm::radians(45.f), width / height, 0.1f, 100.f);
    shader_program.set_mat4("projection", projection);


    vao.bind();
    tex0.bind();
    tex1.bind();
    while (!window.should_close())
    {
        window.poll_events();
        window.process_input();

        glClearColor(0.f, 0.f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (int i = 0; i < 10; ++i)
        {
            glm::mat4 model(1.f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float) glfwGetTime(), glm::vec3(1.f, 0.3f, 0.5f));
            shader_program.set_mat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        window.swap_buffers();
    }

    return 0;
}
