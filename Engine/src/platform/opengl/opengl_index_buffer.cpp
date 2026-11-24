#include "weave/platform/opengl/opengl_index_buffer.h"

#include "glad/glad.h"

namespace Weave::OpenGL {
    IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) {
        this->count = count;

        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &this->id);
    }

    void IndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
    }

    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
