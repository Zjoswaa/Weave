#include "weave/PCH.h"
#include "weave/platform/opengl/opengl_index_buffer.h"

#include <glad/glad.h>

namespace Weave {
    OpenGlIndexBuffer::OpenGlIndexBuffer(const uint32_t* indices, const uint32_t count) {
        this->count = count;

        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGlIndexBuffer::~OpenGlIndexBuffer() {
        glDeleteBuffers(1, &this->id);
    }

    void OpenGlIndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
    }
    
    void OpenGlIndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
