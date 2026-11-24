#include "weave/PCH.h"
#include "weave/core/log.h"
#include "weave/core/window.h"
#include "weave/platform/opengl/opengl_context.h"
#include "weave/renderer/graphics_context.h"
#include "weave/renderer/renderer.h"

namespace Weave {
    std::unique_ptr<GraphicsContext> GraphicsContext::create(const Weave::Window& window) {
        switch (Renderer::get_renderer_api()) {
#ifdef WEAVE_HAS_OPENGL
            case RendererAPI::OpenGL:
                return std::make_unique<OpenGL::Context>(window);
#endif
            case RendererAPI::None:
                WEAVE_LOG_CORE_CRITICAL_TAG("Renderer", "RendererAPI::None selected when creating graphics context");
                return nullptr;
            default:
                WEAVE_LOG_CORE_CRITICAL_TAG("Renderer", "Invalid RendererAPI selected when creating graphics context");
                return nullptr;
        }
    }
}
