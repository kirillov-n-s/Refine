#include <thread>
#include "Refine/Geometry/Common.h"
#include "Demo.h"

void Demo::create(int width, int height, std::string &error)
{
    error = "";

    s_width = width;
    s_height = height;
    s_aspectRatio = (float)s_width / s_height;

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
        Refine::Geometry::MeshTri *mesh,
        Refine::PBD::ProblemPositional *problem,
        Refine::Rendering::GlMesh *glMesh,
        Refine::Rendering::GlShader *glShader)
{
    s_mesh = mesh;
    s_problem = problem;
    s_glMesh = glMesh;
    s_glShader = glShader;
}

void Demo::run()
{
    float currentFrameElapsed;
    float prevFrameElapsed = 0.f;
    float dt;

    s_glShader->use();
    s_glShader->setUniform(
            "uProjection",
            glm::perspective(
                    glm::radians(s_fov),
                    s_aspectRatio,
                    s_near,
                    s_far));
    s_glShader->setUniform("uModel", s_model);
    s_glShader->setUniform("uNormalModel", s_normalModel);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);

    s_camera = {};

    while (!glfwWindowShouldClose(s_window))
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
        runSimulation(dt);
        render();

        glfwSwapBuffers(s_window);
        glfwPollEvents();
    }
}

void Demo::destroy()
{
    delete s_glMesh;
    delete s_glShader;
    glfwTerminate();
}

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

void Demo::runSimulation(const float dt)
{
    s_mesh->vertices = s_problem->solveForPositions(dt);
    s_mesh->normals = Refine::Geometry::computeNormals(s_mesh->vertices, s_mesh->vertexIndices);

    std::vector<Refine::Rendering::Point> points;
    std::vector<unsigned int> indices;
    Refine::Rendering::glBuffers(*s_mesh, points, indices);

    s_glMesh->updateGeometry(points);
}

void Demo::render()
{
    s_glShader->use();
    s_glShader->setUniform("uView", s_camera.view());
    s_glShader->setUniform("uCameraDir", s_camera.front());

    glPolygonOffset(1,1);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    s_glShader->setUniform("uColor", s_surfaceColor);
    s_glMesh->draw();

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDisable(GL_POLYGON_OFFSET_FILL);
    s_glShader->setUniform("uColor", s_wireframeColor);
    s_glMesh->draw();
}
