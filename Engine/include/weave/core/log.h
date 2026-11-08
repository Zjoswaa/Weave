#ifndef WEAVE_LOG_H
#define WEAVE_LOG_H

#include <spdlog/spdlog.h>
#include "spdlog/pattern_formatter.h"

namespace Weave {
    class Log {
    public:
        enum class Type {
            Core = 0,
            Client = 1
        };

        enum class Level {
            Critical = 0,
            Error = 1,
            Warn = 2,
            Info = 3,
            Debug = 4,
            Trace = 5
        };

        struct TagInfo {
            bool enabled = true;
            Level filter = Level::Trace;
        };

        static void init();
        static void shutdown();

        inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return core_logger; }
        inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return client_logger; }

        static void set_default_tag_info();

        template <typename... Args>
        static void print_message(Type type, Level level, std::string_view tag, fmt::format_string<Args...> fmt, Args&&... args) {
            const TagInfo& tag_info = get_tag_info(tag);
            if (!tag_info.enabled || level > tag_info.filter) {
                return;
            }

            std::shared_ptr<spdlog::logger> logger = (type == Type::Core) ? get_core_logger() : get_client_logger();
            if (tag.empty()) {
                switch (level) {
                    case Level::Trace:
                        logger->trace(fmt, std::forward<Args>(args)...);
                        break;
                    case Level::Debug:
                        logger->debug(fmt, std::forward<Args>(args)...);
                        break;
                    case Level::Info:
                        logger->info(fmt, std::forward<Args>(args)...);
                        break;
                    case Level::Warn:
                        logger->warn(fmt, std::forward<Args>(args)...);
                        break;
                    case Level::Error:
                        logger->error(fmt, std::forward<Args>(args)...);
                        break;
                    case Level::Critical:
                        logger->critical(fmt, std::forward<Args>(args)...);
                        break;
                }
            } else {
                switch (level) {
                    case Level::Trace:
                        logger->trace("[{}] {}", tag, fmt::format(fmt, std::forward<Args>(args)...));
                        break;
                    case Level::Debug:
                        logger->debug("[{}] {}", tag, fmt::format(fmt, std::forward<Args>(args)...));
                        break;
                    case Level::Info:
                        logger->info("[{}] {}", tag, fmt::format(fmt, std::forward<Args>(args)...));
                        break;
                    case Level::Warn:
                        logger->warn("[{}] {}", tag, fmt::format(fmt, std::forward<Args>(args)...));
                        break;
                    case Level::Error:
                        logger->error("[{}] {}", tag, fmt::format(fmt, std::forward<Args>(args)...));
                        break;
                    case Level::Critical:
                        logger->critical("[{}] {}", tag, fmt::format(fmt, std::forward<Args>(args)...));
                        break;
                }
            }
        }

    private:
        static std::shared_ptr<spdlog::logger> core_logger;
        static std::shared_ptr<spdlog::logger> client_logger;

        static inline TagInfo default_tag_info{true, Level::Trace};
        inline static std::map<std::string, TagInfo> tag_info_map;

        static const TagInfo& get_tag_info(const std::string_view& tag) {
            const auto it = tag_info_map.find(std::string(tag));
            if (it != tag_info_map.end()) {
                return it->second;
            }

            return default_tag_info;
        }
    };
}

#define WEAVE_LOG_CORE_TRACE(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Trace, "", fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CORE_DEBUG(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Debug, "", fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CORE_INFO(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Info, "", fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CORE_WARN(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Warn, "", fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CORE_ERROR(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Error, "", fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CORE_CRITICAL(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Critical, "", fmt, ##__VA_ARGS__)

#define WEAVE_LOG_CORE_TRACE_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Trace, tag, fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CORE_DEBUG_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Debug, tag, fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CORE_INFO_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Info, tag, fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CORE_WARN_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Warn, tag, fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CORE_ERROR_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Error, tag, fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CORE_CRITICAL_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Core, Weave::Log::Level::Critical, tag, fmt, ##__VA_ARGS__)

#define WEAVE_LOG_TRACE(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Trace, "", fmt, ##__VA_ARGS__)
#define WEAVE_LOG_DEBUG(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Debug, "", fmt, ##__VA_ARGS__)
#define WEAVE_LOG_INFO(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Info, "", fmt, ##__VA_ARGS__)
#define WEAVE_LOG_WARN(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Warn, "", fmt, ##__VA_ARGS__)
#define WEAVE_LOG_ERROR(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Error, "", fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CRITICAL(fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Critical, "", fmt, ##__VA_ARGS__)

#define WEAVE_LOG_TRACE_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Trace, tag, fmt, ##__VA_ARGS__)
#define WEAVE_LOG_DEBUG_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Debug, tag, fmt, ##__VA_ARGS__)
#define WEAVE_LOG_INFO_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Info, tag, fmt, ##__VA_ARGS__)
#define WEAVE_LOG_WARN_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Warn, tag, fmt, ##__VA_ARGS__)
#define WEAVE_LOG_ERROR_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Error, tag, fmt, ##__VA_ARGS__)
#define WEAVE_LOG_CRITICAL_TAG(tag, fmt, ...) Weave::Log::print_message(Weave::Log::Type::Client, Weave::Log::Level::Critical, tag, fmt, ##__VA_ARGS__)

#endif
