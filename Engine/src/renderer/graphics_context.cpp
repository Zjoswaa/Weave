#include "weave/PCH.h"
#include "weave/core/window.h"
#include "weave/platform/opengl/context.h"
#include "weave/renderer/graphics_context.h"

namespace Weave {
    std::unique_ptr<GraphicsContext> GraphicsContext::create(const Weave::Window& window) {
#ifdef WEAVE_HAS_OPENGL
        return std::make_unique<OpenGL::Context>(window);
#endif
    }
}
