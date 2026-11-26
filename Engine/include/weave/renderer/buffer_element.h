#ifndef WEAVE_BUFFER_ELEMENT_H
#define WEAVE_BUFFER_ELEMENT_H

#include "weave/PCH.h"
#include "weave/renderer/shader_data_type.h"
#ifdef WEAVE_HAS_OPENGL
#include "glad/glad.h"
#endif

namespace Weave {
    struct BufferElement {
        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        bool normalized;

        BufferElement() {}

        BufferElement(const ShaderDataType type, const std::string& name, bool normalized = false) {
            this->name = name;
            this->type = type;
            this->size = shader_data_type_size(type);
            this->offset = 0;
            this->normalized = false;
        }

        [[nodiscard]] uint32_t get_component_count() const {
            switch (this->type) {
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3:   return 3 * 3;
                case ShaderDataType::Mat4:   return 4 * 4;
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Bool:   return 1;

                default:
                    WEAVE_LOG_CORE_CRITICAL("Unknown shader data type");
                    return 0;
            }
        }

#ifdef WEAVE_HAS_OPENGL
        [[nodiscard]] GLenum get_opengl_type() const {
            switch (this->type) {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                    return GL_FLOAT;
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                    return GL_INT;
                case ShaderDataType::Bool:
                    return GL_BOOL;

                default:
                    WEAVE_LOG_CORE_CRITICAL("Unknown shader data type");
                    return 0;
            }
        }
#endif
    };
}

#endif
