#include "weave/PCH.h"
#include "weave/renderer/vertex_buffer.h"
#include "weave/platform/opengl/opengl_vertex_buffer.h"

namespace Weave {
    VertexBuffer* VertexBuffer::create(const float* vertices, const uint32_t size) {
        return new OpenGlVertexBuffer(vertices, size);
    }
}
