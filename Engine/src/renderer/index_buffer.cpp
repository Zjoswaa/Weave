#include "weave/PCH.h"
#include "weave/renderer/index_buffer.h"
#include "weave/platform/opengl/opengl_index_buffer.h"

namespace Weave {
    IndexBuffer* IndexBuffer::create(const uint32_t* indices, const uint32_t count) {
        return new OpenGlIndexBuffer(indices, count);
    }
}
