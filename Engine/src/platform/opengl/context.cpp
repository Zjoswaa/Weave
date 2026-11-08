#include "weave/core/log.h"
#include "weave/core/window.h"
#include "weave/platform/opengl/context.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Weave::OpenGL {
    Context::Context(const Weave::Window* window) {
        this->window = window;
    }

    Context::~Context() {
        this->shutdown();
    }

    void Context::init() {
        WEAVE_LOG_CORE_INFO("Creating OpenGL context");

        glfwMakeContextCurrent(static_cast<GLFWwindow*>(this->window->get_native_window()));

        int success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        if (!success) {
            WEAVE_LOG_CORE_CRITICAL_TAG("GLAD", "Failed to initialize");
            return;
        }

        WEAVE_LOG_CORE_INFO("OpenGL Info:");
        WEAVE_LOG_CORE_INFO("  Vendor:   {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
        WEAVE_LOG_CORE_INFO("  Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        WEAVE_LOG_CORE_INFO("  Version:  {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    }

    void Context::shutdown() {
        WEAVE_LOG_CORE_INFO("Destroying OpenGL context");
    }
}
