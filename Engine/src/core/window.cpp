#include "weave/PCH.h"
#include "weave/core/window.h"
#include "weave/platform/glfw/window.h"

namespace Weave {
    std::unique_ptr<Window> Window::create(const WindowSpecification& spec) {
        // TODO: Add platform detection and create the appropriate window type based on the platform.
        return std::make_unique<GLFW::Window>(spec);
    }
}
