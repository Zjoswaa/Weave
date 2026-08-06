#include "weave/renderer/graphics_context.h"
#include "weave/PCH.h"
#include "weave/core/window.h"
#include "weave/platform/opengl/opengl_context.h"

namespace Weave {
    std::unique_ptr<GraphicsContext> GraphicsContext::create(Weave::Window* window) {
        return std::make_unique<OpenGlContext>(window);
    }
}
