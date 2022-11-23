#ifndef REFINE_DEMO_H
#define REFINE_DEMO_H

#include <iostream>
#include "Refine/Rendering/Camera.h"
#include "Refine/Rendering/GlMesh.h"
#include "Refine/Rendering/GlShader.h"
#include "Refine/PBD/ProblemPositional.h"
#include <GLFW/glfw3.h>

class Demo
{
public:
    static void create(int width, int height, std::string &error);
    static void load(
            Refine::Geometry::MeshTri *mesh,
            Refine::PBD::ProblemPositional *problem,
            Refine::Rendering::Buffer *glBuffer,
            Refine::Rendering::GlMesh *glMesh,
            Refine::Rendering::GlShader *glShader);
    static void run();
    static void destroy();

private:
    static inline GLFWwindow* s_window;

    static inline int s_width;
    static inline int s_height;
    static inline float s_aspectRatio;

    static inline float s_sensitivity = 0.1f;
    static inline float s_speed = 2.5f;
    static inline float s_fov = 45.f;
    static inline float s_near = 0.1f;
    static inline float s_far = 1000.f;

    static inline float s_xPrevPos;
    static inline float s_yPrevPos;

    static inline Refine::Geometry::MeshTri *s_mesh;
    static inline Refine::PBD::ProblemPositional *s_problem;

    static inline Refine::Rendering::Buffer *s_buffer;
    static inline Refine::Rendering::GlMesh *s_glMesh;
    static inline Refine::Rendering::GlShader *s_glShader;
    static inline Refine::Rendering::Camera s_camera;

    static inline glm::mat4 s_model = glm::mat4 { 1.f };
    static inline glm::mat4 s_normalModel = glm::transpose(glm::inverse(s_model));

    static inline glm::vec4 s_surfaceColor {0.1f, 0.1f, 0.1f, 1.0f};//{0.7f, 0.5f, 0.4f, 1.0f};//{0.4f, 0.5f, 0.8f, 1.0f};
    static inline glm::vec4 s_wireframeColor {0.65f, 0.65f, 0.65f, 1.0f};//{0.125f, 0.125f, 0.125f, 1.0f};
    static inline glm::vec4 s_backgroundColor {0.4f, 0.4f, 0.4f, 1.0f};

    static inline bool s_isPaused = true;
    static inline bool s_enableFaceCulling = true;

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
    static void runSimulation(const float dt);
    static void updateVisuals();
    static void render();
};

#endif
