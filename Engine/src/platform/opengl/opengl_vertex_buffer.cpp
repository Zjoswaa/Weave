#include "weave/platform/opengl/opengl_vertex_buffer.h"

#include "glad/glad.h"

namespace Weave::OpenGL {
    VertexBuffer::VertexBuffer(float *vertices, uint32_t size) {
        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &this->id);
    }

    void VertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
    }

    void VertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
