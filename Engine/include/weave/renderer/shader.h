#ifndef WEAVE_SHADER_H
#define WEAVE_SHADER_H

#include "weave/PCH.h"

#include <glm/glm.hpp>

namespace Weave {
    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void set_mat4(const std::string& name, const glm::mat4& value) = 0;

        static Shader* create(const std::string& vertex_src, const std::string& fragment_src);
    };
}

#endif
