#ifndef REFINE_RENDERING_GLSHADER_H
#define REFINE_RENDERING_GLSHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Refine::Rendering {

    class GlShader
    {
    public:
        GlShader(
            const std::string &vertPath,
            const std::string &fragPath,
            std::string &error);
        ~GlShader();

        void use() const;

        template <typename U>
        void setUniform(
            const std::string& name,
            const U &value) const;

    private:
        unsigned int m_id;

        int uniformLocation(const std::string& name) const;
    };

    template <typename>
    constexpr bool is_always_false = false;

    template<typename U>
    void GlShader::setUniform(
        const std::string &name,
        const U &value) const
    {
        const int location = uniformLocation(name);
        if constexpr(std::is_same_v<U, float>)
            glUniform1f(location, value);
        else if constexpr(std::is_same_v<U, glm::vec3>)
            glUniform3f(location, value.x, value.y, value.z);
        else if constexpr(std::is_same_v<U, glm::vec4>)
            glUniform4f(location, value.x, value.y, value.z, value.w);
        else if constexpr(std::is_same_v<U, glm::mat4>)
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
        else if constexpr(std::is_same_v<U, int>)
            glUniform1i(location, value);
        else
            static_assert(is_always_false<U>, "Uniform of that type is not supported.");
    }
}

#endif
