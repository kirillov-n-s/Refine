#include <fstream>
#include <sstream>
#include <vector>
#include "GlShader.h"

namespace Refine::Rendering {

    GlShader::GlShader(
        const std::string &vertPath,
        const std::string &fragPath,
        std::string &error)
    {
        error = "";

        std::ifstream vertFile;
        std::ifstream fragFile;

        vertFile.open(vertPath);
        if (!vertFile.is_open()) {
            error = "Cannot open file " + vertPath;
            return;
        }

        fragFile.open(fragPath);
        if (!fragFile.is_open()) {
            error = "Cannot open file " + fragPath;
            return;
        }

        std::ostringstream vertStream;
        std::ostringstream fragStream;

        vertStream << vertFile.rdbuf();
        fragStream << fragFile.rdbuf();

        vertFile.close();
        fragFile.close();

        const std::string vertString = vertStream.str();
        const std::string fragString = fragStream.str();

        const char *vertCode = vertString.c_str();
        const char *fragCode = fragString.c_str();

        unsigned int vertId;
        unsigned int fragId;

        int isSuccess;
        int logLength;
        std::vector<char> log;

        auto compileShader =
        [&isSuccess, &logLength, &log, &error](
            const unsigned int id,
            const char **code,
            const char *type)
        {
            glShaderSource(
                id,
                1,
                code,
                nullptr);
            glCompileShader(id);
            glGetShaderiv(
                id,
                GL_COMPILE_STATUS,
                &isSuccess);
            if(!isSuccess) {
                glGetShaderiv(
                    id,
                    GL_INFO_LOG_LENGTH,
                    &logLength);
                log.resize(logLength);
                glGetShaderInfoLog(
                    id,
                    logLength,
                    nullptr,
                    log.data());
                glDeleteShader(id);
                error = std::string(type) + " shader compilation error. Log:\n" + log.data() + '\n';
            }
        };

        vertId = glCreateShader(GL_VERTEX_SHADER);
        compileShader(
            vertId,
            &vertCode,
            "Point");
        fragId = glCreateShader(GL_FRAGMENT_SHADER);
        compileShader(
            fragId,
            &fragCode,
            "Fragment");

        m_id = glCreateProgram();
        glAttachShader(m_id, vertId);
        glAttachShader(m_id, fragId);
        glLinkProgram(m_id);
        glGetProgramiv(m_id, GL_LINK_STATUS, &isSuccess);
        if(!isSuccess) {
            glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);
            log.resize(logLength);
            glGetProgramInfoLog(m_id, logLength, nullptr, log.data());
            glDeleteProgram(m_id);
            glDeleteShader(vertId);
            glDeleteShader(fragId);
            error = std::string("Program link error. Log:\n") + log.data();
        }

        glDetachShader(m_id, vertId);
        glDetachShader(m_id, fragId);
        glDeleteShader(vertId);
        glDeleteShader(fragId);
    }

    GlShader::~GlShader()
    {
        glDeleteProgram(m_id);
    }

    void GlShader::use() const
    {
        glUseProgram(m_id);
    }

    int GlShader::uniformLocation(const std::string &name) const
    {
        return glGetUniformLocation(m_id, name.c_str());
    }
}
