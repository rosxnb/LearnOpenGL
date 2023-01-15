#include "shader.hpp"
#include "window.hpp"
#include "stb_image.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"

int main()
{
    Window window;

    // Shader Program
    Shader shader_program("./shaders/vertex.glsl", "./shaders/fragment.glsl");
    shader_program.use();

    // Data and data objects
    constexpr float vertices[] = {
        // positions        // colors         // texture coords
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
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
    ibo.record_indices(sizeof(indices), indices);

    // Textures
    unsigned int texture; 
    glGenTextures(1, &texture);
    
    int width, height, num_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("resources/tree.png", &width, &height, &num_channels, 0);
    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "ERROR: texture couldn't be loaded \n";
    }

    stbi_image_free(data);

    while (!window.should_close())
    {
        window.poll_events();
        window.process_input();

        glClearColor(0.f, 0.f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind();
        ibo.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swap_buffers();
    }

    return 0;
}
