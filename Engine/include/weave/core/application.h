#ifndef WEAVE_APPLICATION_H
#define WEAVE_APPLICATION_H

#include "weave/PCH.h"
#include "weave/core/events/event.h"
#include "weave/core/window.h"

namespace Weave {
    struct ApplicationSpecification {
        std::string name = "Application";
        uint32_t window_width = 1280;
        uint32_t window_height = 720;
        bool window_decorated = true;
        bool window_fullscreen = false;
        bool window_maximized = false;
        bool window_resizable = true;
    };

    class Application {
    public:
        Application(const ApplicationSpecification& spec);
        virtual ~Application();

        virtual void run();
        virtual void on_event(const Weave::Event& event);

    private:
        bool running = false;

        ApplicationSpecification spec;
        std::unique_ptr<Weave::Window> window;
    };

    // Implemented by client
    std::unique_ptr<Application> create_application(int argc, char** argv);
}

#endif
