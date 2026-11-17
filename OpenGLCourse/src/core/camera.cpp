// Ad Maiorem Dei Gloriam!

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "core/camera.hpp"

glm::mat4 PerspectiveCamera::getMatrix() const
{
    glm::mat4 view{1.0f}, projection{1.0f};
    view = glm::lookAt(mPosition, mPosition + calculateOrientation(mYaw, mPitch), {0.0f, 1.0f, 0.0f});

    projection = glm::perspective(mFov, mAspectRatio, mNear, mFar);
    return projection * view;
}

void PerspectiveCamera::setViewportSize(glm::vec2 newViewportSize)
{
    Camera::setViewportSize(newViewportSize);
    mAspectRatio = newViewportSize.x / newViewportSize.y;
}

void PerspectiveCamera::lockWindow(GLFWwindow* window)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(window, &lastX, &lastY);
}

void PerspectiveCamera::updateByInputs(GLFWwindow* window, float dt)
{
    const float sensibility = 0.01f;
    const float speed = 10.0f;

    glm::vec3 orientation = calculateOrientation(mYaw, mPitch);
    glm::vec3 right = glm::cross(orientation, mUp);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) mPosition += orientation * speed * dt;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) mPosition -= orientation * speed * dt;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) mPosition += right * speed * dt;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) mPosition -= right * speed * dt;

    double mousePosX, mousePosY;
    glfwGetCursorPos(window, &mousePosX, &mousePosY);
    
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    glm::vec2 mouseOffsetReduced = glm::vec2{ mousePosX - lastX, mousePosY - lastY} * sensibility;
    lastX = mousePosX;
    lastY = mousePosY;
    
    mYaw += mouseOffsetReduced.x;
    mPitch -= mouseOffsetReduced.y;

    constexpr float PI = 3.14159f;
    if (mPitch > PI / 2.0f - 0.14f) mPitch = PI / 2.0f - 0.14f;
    if (mPitch < -PI / 2.0f + 0.14f) mPitch = -PI / 2.0f + 0.14f;

}

glm::vec3 PerspectiveCamera::calculateOrientation(float yaw, float pitch)
{
    return glm::normalize(glm::vec3{cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch)});
}

glm::mat4 OrthographicCamera::getMatrix() const
{
    return glm::ortho(-mViewportSize.x / 2.0f + mPosition.x, mViewportSize.x / 2.0f + mPosition.x, -mViewportSize.y / 2.0f + mPosition.y, mViewportSize.y / 2.0f + mPosition.y, -2.0f, 10.0f);
}