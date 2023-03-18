#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum class CameraMovement 
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
static constexpr float YAW         = -90.0f;
static constexpr float PITCH       =  0.0f;
static constexpr float SPEED       =  2.5f;
static constexpr float SENSITIVITY =  0.1f;
static constexpr float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
    public:
        // camera Attributes
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        // euler Angles
        float m_yaw;
        float m_pitch;

        // camera options
        float m_movementSpeed;
        float m_mouseSensitivity;
        float m_zoom;


        Camera(const Camera&) = delete;
        Camera& operator= (const Camera&) = delete;
        Camera(Camera&&) = delete;
        Camera& operator= (Camera&&) = delete;

        // constructor with vectors
        Camera( glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
                glm::vec3 up = glm::vec3(0.f, 1.f, 0.f),
                float yaw = YAW, float pitch = PITCH );

        // constructor with scalar vlaues
        Camera( float posX, float posY, float posZ,
                float upX, float upY, float upZ, 
                float yaw, float pitch );


        glm::mat4 get_view_matrix();
        void process_keyboard(CameraMovement direction, float deltaTime);
        void process_mouse_movement(float xoffset, float yoffset, GLboolean constrainPitch = true);
        void process_mouse_scroll(float yoffset);

    private:
        void update_camera_vectors();
};

#endif
