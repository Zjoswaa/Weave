#ifndef WEAVE_VERTEX_BUFFER_H
#define WEAVE_VERTEX_BUFFER_H

#include "weave/PCH.h"
#include "weave/renderer/buffer_layout.h"

namespace Weave {
    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const  = 0;

        virtual void set_layout(const BufferLayout& layout) = 0;
        [[nodiscard]] virtual const BufferLayout& get_layout() const = 0;

        static VertexBuffer* create(float* vertices, uint32_t size);
    };
}

#endif
