#ifndef WEAVE_APPLICATION_H
#define WEAVE_APPLICATION_H

#include "Weave/PCH.h"

namespace Weave {
    class Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run();
    };

    // Implemented by client
    std::unique_ptr<Application> CreateApplication(int argc, char** argv);
}

#endif
