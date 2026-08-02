#include "weave/core/core.h"

#include "weave/core/log.h"
#include "weave/core/version.h"

namespace Weave {
    void init_core() {
        Log::init();
        WEAVE_LOG_CORE_INFO_TAG("Core", "Initialized");
        WEAVE_LOG_CORE_INFO_TAG("Core", "Weave Engine {}", WEAVE_VERSION_FULL);
    }

    void shutdown_core() {
        WEAVE_LOG_CORE_INFO_TAG("Core", "Shutting down");
        Log::shutdown();
    }
}
