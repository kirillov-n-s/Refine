#ifndef REFINE_DEMO_H
#define REFINE_DEMO_H

#include <iostream>
#include "Refine/Rendering/Camera.h"
#include "Refine/Rendering/GlMesh.h"
#include "Refine/Rendering/GlShader.h"
#include <GLFW/glfw3.h>

class Demo
{
public:
    static void create(int width, int height, std::string &error);
    static void load(
            Refine::Rendering::GlMesh *mesh,
            Refine::Rendering::GlShader *shader,
            const Refine::Rendering::Camera &camera);
    static void run();
    static void destroy();

private:
    static inline GLFWwindow* s_window;
    static inline int s_width;
    static inline int s_height;
    static inline float s_aspect;

    static inline Refine::Rendering::GlMesh* s_mesh;
    static inline Refine::Rendering::GlShader* s_shader;
    static inline Refine::Rendering::Camera s_camera;

    static inline float s_xPrevPos;
    static inline float s_yPrevPos;

    static inline const float s_sensitivity = 0.1f;
    static inline float s_speed = 2.5f;

    static inline const float s_fov = 45.f;
    static inline const float s_near = 0.1f;
    static inline const float s_far = 1000.f;

    static inline const glm::mat4 s_model = glm::mat4 { 1.f };
    static inline const glm::mat4 s_normalModel = glm::transpose(glm::inverse(s_model));

    static void resizeCallback(
            GLFWwindow*,
            int newWidth,
            int newHeight);
    static void cursorCallback(
            GLFWwindow*,
            double xPos,
            double yPos);
    static void scrollCallback(
            GLFWwindow*,
            double,
            double yOffset);
    static void keyCallback(
            GLFWwindow*,
            int key,
            int,
            int action,
            int);

    static void handleCameraMovement(const float dt);
    static void render();
};

#endif
