#ifndef WEAVE_BUFFER_LAYOUT_H
#define WEAVE_BUFFER_LAYOUT_H

#include "weave/PCH.h"

namespace Weave {
    enum class ShaderDataType {
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

    static constexpr uint32_t get_shader_data_type_size(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
                return 4;
            case ShaderDataType::Float2:
                return 4 * 2;
            case ShaderDataType::Float3:
                return 4 * 3;
            case ShaderDataType::Float4:
                return 4 * 4;
            case ShaderDataType::Mat3:
                return 4 * 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4 * 4;
            case ShaderDataType::Int:
                return 4;
            case ShaderDataType::Int2:
                return 4 * 2;
            case ShaderDataType::Int3:
                return 4 * 3;
            case ShaderDataType::Int4:
                return 4 * 4;
            case ShaderDataType::Bool:
                return 1;
        }
        return 0;
    }

    struct BufferElement {
        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        bool normalized;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) {
            this->name = name;
            this->type = type;
            this->size = get_shader_data_type_size(type);
            this->offset = 0;
            this->normalized = normalized;
        }

        constexpr uint32_t get_component_count() const {
            switch (type) {
                case ShaderDataType::Float:
                    return 1;
                case ShaderDataType::Float2:
                    return 2;
                case ShaderDataType::Float3:
                    return 3;
                case ShaderDataType::Float4:
                    return 4;
                case ShaderDataType::Mat3:
                    return 3 * 3;
                case ShaderDataType::Mat4:
                    return 4 * 4;
                case ShaderDataType::Int:
                    return 1;
                case ShaderDataType::Int2:
                    return 2;
                case ShaderDataType::Int3:
                    return 3;
                case ShaderDataType::Int4:
                    return 4;
                case ShaderDataType::Bool:
                    return 1;
            }
            return 0;
        }
    };

    class BufferLayout {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements) {
            this->elements = elements;
            calculate_offsets_and_stride();
        }

        inline uint32_t get_stride() const { return this->stride; }
        inline const std::vector<BufferElement>& get_elements() const { return this->elements; }

        std::vector<BufferElement>::iterator begin() { return this->elements.begin(); }
        std::vector<BufferElement>::iterator end() { return this->elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return this->elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return this->elements.end(); }

    private:
        void calculate_offsets_and_stride() {
            uint32_t offset = 0;
            this->stride = 0;
            for (auto& element : this->elements) {
                element.offset = offset;
                offset += element.size;
                this->stride += element.size;
            }
        }

    private:
        std::vector<BufferElement> elements;
        uint32_t stride = 0;
    };
}

#endif
