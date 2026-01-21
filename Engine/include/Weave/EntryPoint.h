#ifndef WEAVE_ENTRYPOINT_H
#define WEAVE_ENTRYPOINT_H

#include "Weave/Core/Application.h"
#include "Weave/Core/Core.h"

int main(int argc, char** argv) {
    Weave::InitCore();
    const std::unique_ptr<Weave::Application> app = Weave::CreateApplication(argc, argv);
    app->Run();
    Weave::ShutdownCore();
    return 0;
}

#endif
