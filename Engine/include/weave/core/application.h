#ifndef WEAVE_APPLICATION_H
#define WEAVE_APPLICATION_H

#include "weave/PCH.h"
#include "weave/core/events/event.h"
#include "weave/core/window.h"

namespace Weave {
    class Application {
    public:
        Application();
        virtual ~Application();

        virtual void run();
        virtual void on_event(Weave::Event& event);

    private:
        bool running = false;

        std::unique_ptr<Weave::Window> window;
    };

    // Implemented by client
    std::unique_ptr<Application> create_application(int argc, char** argv);
}

#endif
