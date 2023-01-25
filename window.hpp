#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

class Window 
{
    public:
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(int width = 800, int height = 600);

        bool should_close() const;
        void swap_buffers() const;
        void poll_events() const;
        void process_input() const;

        std::pair<float, float> get_buffer_size();

        ~Window();

    private:
        int m_width, m_height;
        GLFWwindow *m_window;

        static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
        void clear();
};

#endif
