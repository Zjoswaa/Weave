#ifdef WEAVE_HAS_OPENGL

#include "weave/core/log.h"
#include "weave/core/window.h"
#include "weave/platform/opengl/opengl_context.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Weave::OpenGL {
    Context::Context(const Weave::Window& window) : window(window) { }

    Context::~Context() {
        this->shutdown();
    }

    bool Context::init() {
        WEAVE_LOG_CORE_INFO("Creating OpenGL context");

        // TODO: Move this and GraphicsContext to a renderer class
        glfwMakeContextCurrent(static_cast<GLFWwindow*>(this->window.get_native_window()));

        int success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        if (!success) {
            WEAVE_LOG_CORE_CRITICAL_TAG("GLAD", "Failed to initialize");
            return false;
        }

        WEAVE_LOG_CORE_INFO("OpenGL Info:");
        WEAVE_LOG_CORE_INFO("  Vendor:   {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
        WEAVE_LOG_CORE_INFO("  Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        WEAVE_LOG_CORE_INFO("  Version:  {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

        return true;
    }

    void Context::shutdown() {
        WEAVE_LOG_CORE_INFO("Destroying OpenGL context");
        glfwMakeContextCurrent(nullptr);
    }
}

#endif // WEAVE_HAS_OPENGL
