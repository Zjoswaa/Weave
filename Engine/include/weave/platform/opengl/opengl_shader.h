#ifndef WEAVE_OPENGL_SHADER_H
#define WEAVE_OPENGL_SHADER_H

#include "weave/PCH.h"
#include "weave/renderer/shader.h"

#include <glad/glad.h>

namespace Weave {
    class OpenGlShader : public Shader {
    public:
        OpenGlShader(const std::string& vertex_src, const std::string& fragment_src);
        ~OpenGlShader() override;

        void bind() const override;
        void unbind() const override;

    private:
        GLuint id;
    };
}

#endif
