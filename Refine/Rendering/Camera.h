#ifndef REFINE_RENDERING_CAMERA_H
#define REFINE_RENDERING_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Refine::Rendering {

    class Camera
    {
    public:
        Camera(
                const glm::vec3 &position = {0.0f, 0.0f, 3.0f},
                const float yaw = -90.f,
                const float pitch = 0.f);

        glm::vec3 front() const;
        glm::vec3 right() const;
        glm::vec3 up() const;

        glm::mat4 view() const;

        void move(const glm::vec3& offset);
        void rotate(
                const float yawOffset,
                const float pitchOffset);

    private:
        glm::vec3 m_position;
        float m_yaw;
        float m_pitch;

        glm::vec3 m_front;
        glm::vec3 m_right;
        glm::vec3 m_up;

        void updateDerivedVectors();
    };
}

#endif
