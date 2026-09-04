#include "weave/PCH.h"
#include "weave/platform/opengl/opengl_vertex_buffer.h"

#include <glad/glad.h>

namespace Weave {
    OpenGlVertexBuffer::OpenGlVertexBuffer(const float* vertices, const uint32_t size) {
        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGlVertexBuffer::~OpenGlVertexBuffer() {
        glDeleteBuffers(1, &this->id);
    }

    void OpenGlVertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
    }
    
    void OpenGlVertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
