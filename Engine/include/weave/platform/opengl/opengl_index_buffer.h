#ifndef WEAVE_OPENGL_INDEX_BUFFER_H
#define WEAVE_OPENGL_INDEX_BUFFER_H

#include "weave/PCH.h"
#include "weave/renderer/index_buffer.h"

#include <glad/glad.h>

namespace Weave {
    class OpenGlIndexBuffer : public IndexBuffer {
    public:
        OpenGlIndexBuffer(const uint32_t* indices, const uint32_t count);
        ~OpenGlIndexBuffer() override;

        void bind() const override;
        void unbind() const override;
        uint32_t get_count() const override { return this->count; }

    private:
        GLuint id;
        uint32_t count;
    };
}

#endif
