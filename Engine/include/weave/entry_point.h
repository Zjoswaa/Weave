#ifndef WEAVE_ENTRYPOINT_H
#define WEAVE_ENTRYPOINT_H

#include "core/application.h"
#include "core/core.h"
#include "core/log.h"

int main(int argc, char** argv) {
    Weave::init_core();
    try {
        const std::unique_ptr<Weave::Application> app = Weave::create_application(argc, argv);
        app->run();
    } catch (const std::exception& e) {
        WEAVE_LOG_CORE_CRITICAL_TAG("Exception", "{}", e.what());
    }
    Weave::shutdown_core();
    return 0;
}

#endif
