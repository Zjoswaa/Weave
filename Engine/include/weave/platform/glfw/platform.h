#ifndef WEAVE_GLFW_PLATFORM_H
#define WEAVE_GLFW_PLATFORM_H
#ifdef WEAVE_WINDOWING_BACKEND_GLFW

#include "weave/platform/platform.h"

namespace Weave::GLFW {
    class Platform : public Weave::Platform {
    public:
        ~Platform() override;

        bool init() override;

    private:
        void shutdown();
    };
}

#endif // WEAVE_WINDOWING_BACKEND_GLFW
#endif // WEAVE_GLFW_PLATFORM_H
