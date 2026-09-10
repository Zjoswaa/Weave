#include "weave/PCH.h"
#include "weave/platform/opengl/opengl_vertex_array.h"
#include "weave/renderer/buffer_layout.h"

#include <glad/glad.h>

namespace Weave {
    static constexpr GLenum shader_data_type_to_opengl_base_type(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
                return GL_FLOAT;
            case ShaderDataType::Float2:
                return GL_FLOAT;
            case ShaderDataType::Float3:
                return GL_FLOAT;
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Mat3:
                return GL_FLOAT;
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
                return GL_INT;
            case ShaderDataType::Int2:
                return GL_INT;
            case ShaderDataType::Int3:
                return GL_INT;
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
        }
        return 0;
    }

    OpenGlVertexArray::OpenGlVertexArray() {
        glGenVertexArrays(1, &this->id);
    }

    OpenGlVertexArray::~OpenGlVertexArray() {
        glDeleteVertexArrays(1, &this->id);
    }

    void OpenGlVertexArray::bind() const {
        glBindVertexArray(this->id);
    }

    void OpenGlVertexArray::unbind() const {
        glBindVertexArray(0);
    }

    void OpenGlVertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) {
        this->bind();
        vertex_buffer->bind();

        uint32_t index = 0;
        const BufferLayout& layout = vertex_buffer->get_layout();
        for (const BufferElement& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.get_component_count(), shader_data_type_to_opengl_base_type(element.type), element.normalized ? GL_TRUE : GL_FALSE, layout.get_stride(), (const void*)(intptr_t)element.offset);
            index++;
        }

        this->vertex_buffers.push_back(vertex_buffer);
    }

    void OpenGlVertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer>& index_buffer) {
        glBindVertexArray(this->id);
        index_buffer->bind();
        this->index_buffer = index_buffer;
    }
}
