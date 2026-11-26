#ifndef WEAVE_SHADER_DATA_TYPE_H
#define WEAVE_SHADER_DATA_TYPE_H

#include "weave/PCH.h"
#include "weave/core/log.h"

namespace Weave {
    enum class ShaderDataType : uint32_t {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    static uint32_t shader_data_type_size(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;
            case ShaderDataType::Bool:   return 1;

            default:
                WEAVE_LOG_CORE_CRITICAL("Unknown shader data type");
                return 0;
        }
    }
}

#endif
