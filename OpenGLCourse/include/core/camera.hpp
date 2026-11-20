// Ad Maiorem Dei Gloriam!
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera(glm::vec2 viewportSize = { 1280.0f, 720.0f }) :
        mViewportSize{ viewportSize } {};

    virtual glm::mat4 getMatrix() const = 0;
    virtual void setViewportSize(glm::vec2 newViewportSize)
    {
        mViewportSize = newViewportSize;
    }

protected:
    glm::vec2 mViewportSize;

};

class PerspectiveCamera final : public Camera 
{
public:
    PerspectiveCamera(glm::vec2 viewportSize = { 1280.0f, 720.0f }) : Camera(viewportSize) {};

    virtual glm::mat4 getMatrix() const override;
    virtual void setViewportSize(glm::vec2 newViewportSize) override;

    void lockWindow(GLFWwindow* window);
    void updateByInputs(GLFWwindow* window, float delta);

    const glm::vec3 getPosition() const { return mPosition; }
    static glm::vec3 calculateOrientation(float yaw, float pitch);

private:
    glm::vec3 mPosition{ 0.0f, 0.0f, 0.0f }, mUp{ 0.0f, 1.0f, 0.0f };
    float mYaw{ -90.0f }, mPitch{ 0.0f };

    float mFov{ glm::radians(120.0f) }, mFar{ 200.0f }, mNear{ 0.1f };
    float mAspectRatio = mViewportSize.x / mViewportSize.y;

    double lastX, lastY;
};

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(glm::vec2 viewportSize = { 1280.0f, 720.0f }) : Camera(viewportSize) {};
    virtual glm::mat4 getMatrix() const override;

private:
    glm::vec2 mPosition{ 0.0f, 0.0f };
    glm::vec2 zoom;
    float rotation = 0.0f;
};

#endif