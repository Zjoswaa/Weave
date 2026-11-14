#include "weave/PCH.h"
#include "weave/platform/glfw/glfw_platform.h"
#include "weave/platform/platform.h"

namespace Weave {
    std::unique_ptr<Platform> Platform::create() {
#ifdef WEAVE_WINDOWING_BACKEND_GLFW
        return std::make_unique<GLFW::Platform>();
#endif
    }
}
