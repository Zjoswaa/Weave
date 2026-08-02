#include "weave/core/log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Weave {
    std::shared_ptr<spdlog::logger> Log::core_logger;
    std::shared_ptr<spdlog::logger> Log::client_logger;

    void Log::init() {
        // spdlog::set_pattern("%^[%T] %n: %v%$");
        core_logger = spdlog::stdout_color_mt("Weave");
        // coreLogger->set_pattern("%^%Y-%m-%dT%H:%M:%S.%e%z | %-8l | %-6n | %v%$", spdlog::pattern_time_type::utc);
        core_logger->set_pattern("%^%H:%M:%S.%e | %-8l | %-5t | %-6n | %v%$");
        core_logger->set_level(spdlog::level::trace);

        client_logger = spdlog::stdout_color_mt("Client");
        // clientLogger->set_pattern("%^%Y-%m-%dT%H:%M:%S.%e%z | %-8l | %-6n | %v%$", spdlog::pattern_time_type::utc);
        client_logger->set_pattern("%^%H:%M:%S.%e | %-8l | %-5t | %-6n | %v%$");
        client_logger->set_level(spdlog::level::trace);

        set_default_tag_info();
    }

    void Log::shutdown() {
        client_logger.reset();
        core_logger.reset();
        spdlog::drop_all();
    }

    void Log::set_default_tag_info() {
        tag_info_map = {
            std::pair<const std::string, TagInfo>("Core", TagInfo(true, Level::Trace))
        };
    }
}
