#ifndef WEAVE_OPENGL_VERTEX_BUFFER_H
#define WEAVE_OPENGL_VERTEX_BUFFER_H

#include "weave/PCH.h"
#include "weave/renderer/vertex_buffer.h"

namespace Weave::OpenGL {
    class VertexBuffer : public Weave::VertexBuffer {
    public:
        VertexBuffer(float* vertices, uint32_t size);
        ~VertexBuffer() override;

        void bind() const override;
        void unbind() const override;

    private:
        uint32_t id;
    };
}

#endif
