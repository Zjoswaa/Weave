#ifndef WEAVE_APPLICATION_H
#define WEAVE_APPLICATION_H

#include "weave/PCH.h"
#include "weave/core/window.h"

namespace Weave {
    class Application {
    public:
        Application();
        virtual ~Application();

        void run();

        virtual void on_event(Weave::Event& event);

    private:
        std::unique_ptr<Window> window;
        bool running = true;
    };

    // Implemented by client
    std::unique_ptr<Application> create_application(int argc, char** argv);
}

#endif
