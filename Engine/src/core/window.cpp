#include "weave/PCH.h"
#include "weave/core/window.h"
#ifdef WEAVE_WINDOWING_BACKEND_GLFW
#include "weave/platform/glfw/glfw_window.h"
#endif

namespace Weave {
    std::unique_ptr<Window> Window::create(const WindowSpecification& spec) {
#ifdef WEAVE_WINDOWING_BACKEND_GLFW
        return std::make_unique<GLFW::Window>(spec);
#endif
    }
}
