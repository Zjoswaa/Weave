#ifndef WEAVE_OPENGL_VERTEX_BUFFER_H
#define WEAVE_OPENGL_VERTEX_BUFFER_H

#include "weave/PCH.h"
#include "weave/renderer/buffer_layout.h"
#include "weave/renderer/vertex_buffer.h"

#include <glad/glad.h>

namespace Weave {
    class OpenGlVertexBuffer : public VertexBuffer {
    public:
        OpenGlVertexBuffer(const float* vertices, const uint32_t size);
        ~OpenGlVertexBuffer() override;

        void bind() const override;
        void unbind() const override;

        const BufferLayout& get_layout() const override;
        void set_layout(const BufferLayout& layout) override;

    private:
        GLuint id;
        BufferLayout layout;
    };
}

#endif
