#include "camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_front(glm::vec3(0.f, 0.f, -1.f)), m_movementSpeed(SPEED),
      m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
    m_position = position;
    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;
    update_camera_vectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
    : m_front(glm::vec3(0.f, 0.f, -1.f)), m_movementSpeed(SPEED),
      m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
    m_position = glm::vec3(posX, posY, posZ);
    m_worldUp = glm::vec3(upX, upY, upZ);
    m_yaw = yaw;
    m_pitch = pitch;
    update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::process_keyboard(CameraMovement direction, float deltaTime)
{
    float velocity = m_movementSpeed * deltaTime;

    if (direction == CameraMovement::FORWARD)
        m_position += m_front * velocity;
    if (direction == CameraMovement::BACKWARD)
        m_position -= m_front * velocity;
    if (direction == CameraMovement::LEFT)
        m_position -= m_right * velocity;
    if (direction == CameraMovement::RIGHT)
        m_position += m_right * velocity;
}

void Camera::process_mouse_movement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw   += xoffset;
    m_pitch += yoffset;

    // make sure when pitch is out of bounds, the screen doesn't get flipped
    if (constrainPitch)
    {
        if (m_pitch > 89.f)
            m_pitch = 89.f;
        if (m_pitch < -89.f)
            m_pitch = -89.f;
    }

    update_camera_vectors();
}

void Camera::process_mouse_scroll(float yoffset)
{
    m_zoom -= static_cast<float>(yoffset);

    if (m_zoom < 1.f)
        m_zoom = 1.f;
    if (m_zoom > 45.f)
        m_zoom = 45.f;
}

void Camera::update_camera_vectors()
{
    glm::vec3 front;
    // calculate the new direction
    front.x = cos(glm::radians(m_yaw) * cos(glm::radians(m_pitch)));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw) * cos(glm::radians(m_pitch)));
    // assign the new calculated direction, magnitude is not needed
    m_front = glm::normalize(front);

    // re-calculate right and up vectors 
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}
