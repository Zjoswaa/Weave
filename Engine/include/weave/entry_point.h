#ifndef WEAVE_ENTRYPOINT_H
#define WEAVE_ENTRYPOINT_H

#include "weave/core/application.h"
#include "weave/core/core.h"

int main(const int argc, char** argv) {
    Weave::init_core();
    {
        const std::unique_ptr<Weave::Application> app = Weave::create_application(argc, argv);
        app->run();
    }
    Weave::shutdown_core();
    return 0;
}

#endif
