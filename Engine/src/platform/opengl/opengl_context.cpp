#include "weave/platform/opengl/opengl_context.h"
#include "weave/core/window.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "weave/core/log.h"

namespace Weave {
    OpenGlContext::OpenGlContext(const Weave::Window* window) {
        this->window = window;
    }

    OpenGlContext::~OpenGlContext() {
        this->shutdown();
    }

    void OpenGlContext::init() {
        WEAVE_LOG_CORE_INFO("Creating graphics context");

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

    void OpenGlContext::shutdown() { }
}
