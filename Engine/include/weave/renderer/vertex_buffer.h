#ifndef WEAVE_VERTEX_BUFFER_H
#define WEAVE_VERTEX_BUFFER_H

#include "weave/PCH.h"

namespace Weave {
    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static VertexBuffer* create(const float* vertices, const uint32_t size);
    };
}

#endif
