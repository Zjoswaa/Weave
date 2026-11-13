#ifndef WEAVE_PLATFORM_H
#define WEAVE_PLATFORM_H

#include "weave/PCH.h"

namespace Weave {
    class Platform {
    public:
        Platform() = default;
        virtual ~Platform() = default;

        virtual bool init() = 0;

        static std::unique_ptr<Platform> create();
    };
}

#endif
