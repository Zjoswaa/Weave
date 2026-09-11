#ifndef WEAVE_OPENGL_SHADER_H
#define WEAVE_OPENGL_SHADER_H

#include "weave/PCH.h"
#include "weave/renderer/shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Weave {
    class OpenGlShader : public Shader {
    public:
        OpenGlShader(const std::string& vertex_src, const std::string& fragment_src);
        ~OpenGlShader() override;

        void bind() const override;
        void unbind() const override;

        void set_mat4(const std::string& name, const glm::mat4& value) override;

    private:
        GLuint id;
    };
}

#endif
