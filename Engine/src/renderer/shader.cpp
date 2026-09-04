#include "weave/PCH.h"
#include "weave/renderer/shader.h"
#include "weave/platform/opengl/opengl_shader.h"

namespace Weave {
    Shader* Shader::create(const std::string& vertex_src, const std::string& fragment_src) {
        return new OpenGlShader(vertex_src, fragment_src);
    }
}