#include "Weave/Core/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Weave {
    std::shared_ptr<spdlog::logger> Log::coreLogger;
    std::shared_ptr<spdlog::logger> Log::clientLogger;

    void Log::Init() {
        // spdlog::set_pattern("%^[%T] %n: %v%$");
        coreLogger = spdlog::stdout_color_mt("Weave");
        // coreLogger->set_pattern("%^%Y-%m-%dT%H:%M:%S.%e%z | %-8l | %-6n | %v%$", spdlog::pattern_time_type::utc);
        coreLogger->set_pattern("%^%H:%M:%S.%e | %-8l | %-5t | %-6n | %v%$");
        coreLogger->set_level(spdlog::level::trace);

        clientLogger = spdlog::stdout_color_mt("Client");
        // clientLogger->set_pattern("%^%Y-%m-%dT%H:%M:%S.%e%z | %-8l | %-6n | %v%$", spdlog::pattern_time_type::utc);
        clientLogger->set_pattern("%^%H:%M:%S.%e | %-8l | %-5t | %-6n | %v%$");
        clientLogger->set_level(spdlog::level::trace);

        SetDefaultTagInfo();
    }

    void Log::Shutdown() {
        clientLogger.reset();
        coreLogger.reset();
        spdlog::drop_all();
    }

    void Log::SetDefaultTagInfo() {
        tagInfoMap = {
            std::pair<const std::string, TagInfo>("Core", TagInfo(true, Level::Trace))
        };
    }
}
