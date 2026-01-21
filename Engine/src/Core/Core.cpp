#include "Weave/Core/Core.h"

#include "Weave/Core/Log.h"
#include "Weave/Core/Version.h"

namespace Weave {
    void InitCore() {
        Log::Init();
        WEAVE_LOG_CORE_INFO_TAG("Core", "Initialized");
        WEAVE_LOG_CORE_INFO_TAG("Core", "Weave Engine {}", WEAVE_VERSION_FULL);
    }

    void ShutdownCore() {
        WEAVE_LOG_CORE_INFO_TAG("Core", "Shutting down");
        Log::Shutdown();
    }
}
