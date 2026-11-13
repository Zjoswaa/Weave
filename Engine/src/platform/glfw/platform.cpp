#ifdef WEAVE_WINDOWING_BACKEND_GLFW

#include "weave/core/log.h"
#include "weave/platform/glfw/platform.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace Weave::GLFW {
    static void glfw_error_callback(int error, const char* description) {
        WEAVE_LOG_CORE_ERROR_TAG("GLFW", "Error ({}): {}", error, description);
    }

    Platform::~Platform() {
        this->shutdown();
    }

    bool Platform::init() {
        WEAVE_LOG_CORE_INFO_TAG("GLFW", "Initializing");
        glfwSetErrorCallback(glfw_error_callback);

        if (glfwInit() != GLFW_TRUE) {
            WEAVE_LOG_CORE_CRITICAL_TAG("GLFW", "Failed to initialize");
            glfwTerminate();
            return false;
        }

        return true;
    }

    void Platform::shutdown() {
        WEAVE_LOG_CORE_INFO_TAG("GLFW", "Shutting down");
        glfwTerminate();
    }
}

#endif // WEAVE_WINDOWING_BACKEND_GLFW
