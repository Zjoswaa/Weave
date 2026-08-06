#include "weave/PCH.h"
#include "weave/core/window.h"
#include "weave/platform/glfw/glfw_window.h"

namespace Weave {
    std::unique_ptr<Window> Window::create(const WindowSpecification& spec) {
        // TODO: Add checks for windowing backends and return different window based on that
        return std::make_unique<GlfwWindow>(spec);
    }
}
