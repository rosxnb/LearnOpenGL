#include "window.hpp"

Window::Window(int width, int height, const char* title)
{
    m_width = width;
    m_height = height;
    
    if (!glfwInit())
    {
        std::cout << "GLFW couldn't get initiallized :( \n";
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
    if (!m_window)
    {
        std::cout << "GLFW faild to create window :( \n";
        return;
    }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "glad could load the opengl funtions correctly";
        return;
    }
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

bool Window::should_close() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::swap_buffers() const
{
    glfwSwapBuffers(m_window);
}

void Window::poll_events() const
{
    glfwPollEvents();
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::process_input() const
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, GL_TRUE);

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Window::clear()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

std::pair<float, float> Window::get_buffer_size()
{
    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    return {static_cast<float>(m_width), static_cast<float>(m_height)};
}

GLFWwindow* Window::get_window()
{
    return m_window;
}

Window::~Window()
{
    clear();
}
