#include "weave/core/log.h"
#include "weave/renderer/renderer.h"
#include "weave/renderer/index_buffer.h"
#include "weave/platform/opengl/opengl_index_buffer.h"

namespace Weave {
    IndexBuffer* IndexBuffer::create(uint32_t *indices, uint32_t count) {
        switch (Renderer::get_renderer_api()) {
#ifdef WEAVE_HAS_OPENGL
            case RendererAPI::OpenGL:
                return new OpenGL::IndexBuffer(indices, count);
#endif
            case RendererAPI::None:
                WEAVE_LOG_CORE_CRITICAL_TAG("Renderer", "RendererAPI::None selected when creating index buffer");
                return nullptr;
            default:
                WEAVE_LOG_CORE_CRITICAL_TAG("Renderer", "Invalid RendererAPI selected when creating index buffer");
                return nullptr;
        }
    }
}
