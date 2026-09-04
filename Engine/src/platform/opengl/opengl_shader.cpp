#include "weave/PCH.h"
#include "weave/platform/opengl/opengl_shader.h"

#include <glad/glad.h>

namespace Weave {
    OpenGlShader::OpenGlShader(const std::string& vertex_src, const std::string& fragment_src) {
        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        const char* vertex_src_c_str = vertex_src.c_str();
        glShaderSource(vertex_shader, 1, &vertex_src_c_str, NULL);
        glCompileShader(vertex_shader);

        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragment_src_c_str = fragment_src.c_str();
        glShaderSource(fragment_shader, 1, &fragment_src_c_str, NULL);
        glCompileShader(fragment_shader);

        this->id = glCreateProgram();
        glAttachShader(this->id, vertex_shader);
        glAttachShader(this->id, fragment_shader);
        glLinkProgram(this->id);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    OpenGlShader::~OpenGlShader() {
        glDeleteProgram(this->id);
    }

    void OpenGlShader::bind() const {
        glUseProgram(this->id);
    }

    void OpenGlShader::unbind() const {
        glUseProgram(0);
    }
}
