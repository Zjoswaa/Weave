#include "weave/core/log.h"
#include "weave/renderer/renderer.h"
#include "weave/renderer/vertex_buffer.h"
#include "weave/platform/opengl/opengl_vertex_buffer.h"

namespace Weave {
    VertexBuffer *VertexBuffer::create(float *vertices, uint32_t size) {
        switch (Renderer::get_renderer_api()) {
#ifdef WEAVE_HAS_OPENGL
            case RendererAPI::OpenGL:
                return new OpenGL::VertexBuffer(vertices, size);
#endif
            case RendererAPI::None:
                WEAVE_LOG_CORE_CRITICAL_TAG("Renderer", "RendererAPI::None selected when creating vertex buffer");
                return nullptr;
            default:
                WEAVE_LOG_CORE_CRITICAL_TAG("Renderer", "Invalid RendererAPI selected when creating vertex buffer");
                return nullptr;
        }
    }
}
