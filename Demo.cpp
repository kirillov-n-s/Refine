#include "Demo.h"

void Demo::resizeCallback(
        GLFWwindow*,
        int newWidth,
        int newHeight)
{
    glViewport(
            0,
            0,
            s_width = newWidth,
            s_height = newHeight);
}

void Demo::cursorCallback(
        GLFWwindow*,
        double xPos,
        double yPos)
{
    float x_offset = xPos - s_xPrevPos;
    float y_offset = s_yPrevPos - yPos;
    s_xPrevPos = xPos;
    s_yPrevPos = yPos;
    s_camera.rotate(
            x_offset * s_sensitivity,
            y_offset * s_sensitivity);
}

void Demo::scrollCallback(
        GLFWwindow*,
        double,
        double yOffset)
{
    if ((s_speed += yOffset) < 0.f)
        s_speed = 0.f;
}

void Demo::keyCallback(
        GLFWwindow*,
        int key,
        int,
        int action,
        int)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(s_window, GLFW_TRUE);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        glfwMaximizeWindow(s_window);
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        s_camera = {};
}

void Demo::handleCameraMovement(const float dt)
{
    glm::vec3 direction { 0.0f, 0.0f, 0.0f };
    if (glfwGetKey(s_window, GLFW_KEY_W) == GLFW_PRESS)
        direction += s_camera.front();
    if (glfwGetKey(s_window, GLFW_KEY_S) == GLFW_PRESS)
        direction -= s_camera.front();
    if (glfwGetKey(s_window, GLFW_KEY_D) == GLFW_PRESS)
        direction += s_camera.right();
    if (glfwGetKey(s_window, GLFW_KEY_A) == GLFW_PRESS)
        direction -= s_camera.right();
    if (glfwGetKey(s_window, GLFW_KEY_Q) == GLFW_PRESS)
        direction += glm::vec3 { 0.0f, 1.0f, 0.0f };
    if (glfwGetKey(s_window, GLFW_KEY_E) == GLFW_PRESS)
        direction -= glm::vec3 { 0.0f, 1.0f, 0.0f };
    s_camera.move(direction * dt * s_speed);
}

void Demo::render()
{
    s_shader->use();
    s_shader->setUniform("uView", s_camera.view());
    s_shader->setUniform("uCameraDir", s_camera.front());

    glPolygonOffset(1,1);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    s_shader->setUniform("uColor", s_surfaceColor);
    s_mesh->draw();

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDisable(GL_POLYGON_OFFSET_FILL);
    s_shader->setUniform("uColor", s_wireframeColor);
    s_mesh->draw();
}

void Demo::create(int width, int height, std::string &error)
{
    error = "";

    s_width = width;
    s_height = height;
    s_aspect = (float)s_width / s_height;

    glfwInit();
    glfwWindowHint(
            GLFW_CONTEXT_VERSION_MAJOR,
            3);
    glfwWindowHint(
            GLFW_CONTEXT_VERSION_MINOR,
            3);
    glfwWindowHint(
            GLFW_OPENGL_PROFILE,
            GLFW_OPENGL_CORE_PROFILE);

    s_window = glfwCreateWindow(
            s_width,
            s_height,
            "",
            nullptr,
            nullptr);
    if (s_window == nullptr) {
        glfwTerminate();
        error = "Cannot open window.";
    }

    glfwMakeContextCurrent(s_window);

    glfwSetInputMode(
            s_window,
            GLFW_CURSOR,
            GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(s_window, resizeCallback);
    glfwSetCursorPosCallback(s_window, cursorCallback);
    glfwSetScrollCallback(s_window, scrollCallback);
    glfwSetKeyCallback(s_window, keyCallback);

    glViewport(
            0,
            0,
            s_width,
            s_height);

    glewInit();
}

void Demo::load(
        Refine::Rendering::GlMesh *mesh,
        Refine::Rendering::GlShader *shader,
        const Refine::Rendering::Camera &camera)
{
    s_mesh = mesh;
    s_shader = shader;
    s_camera = camera;
}

void Demo::run()
{
    float currentFrameElapsed;
    float prevFrameElapsed = 0.f;
    float dt;

    s_shader->use();
    s_shader->setUniform(
            "uProjection",
            glm::perspective(
                    glm::radians(s_fov),
                    s_aspect,
                    s_near,
                    s_far));
    s_shader->setUniform("uModel", s_model);
    s_shader->setUniform("uNormalModel", s_normalModel);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(s_window))
    {
        currentFrameElapsed = glfwGetTime();
        dt = currentFrameElapsed - prevFrameElapsed;
        prevFrameElapsed = currentFrameElapsed;

        glfwSetWindowTitle(
                s_window,
                (std::to_string((int)(1.f / dt)) + " fps").c_str());

        glClearColor(
                s_backgroundColor.r,
                s_backgroundColor.g,
                s_backgroundColor.b,
                s_backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        handleCameraMovement(dt);
        render();

        glfwSwapBuffers(s_window);
        glfwPollEvents();
    }
}

void Demo::destroy()
{
    delete s_mesh;
    delete s_shader;
    glfwTerminate();
}
