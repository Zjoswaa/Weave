#include <Weave.h>

class Sandbox : public Weave::Application {
public:
    Sandbox(int argc, char** argv) {
        WEAVE_LOG_TRACE("Trace");
        WEAVE_LOG_DEBUG("Debug");
        WEAVE_LOG_INFO("Info");
        WEAVE_LOG_WARN("Warn");
        WEAVE_LOG_ERROR("Error");
        WEAVE_LOG_CRITICAL("Critical");

        WEAVE_LOG_TRACE_TAG("Core", "Trace");
        WEAVE_LOG_DEBUG_TAG("Core", "Debug");
        WEAVE_LOG_INFO_TAG("Core", "Info");
        WEAVE_LOG_WARN_TAG("Core", "Warn");
        WEAVE_LOG_ERROR_TAG("Core", "Error");
        WEAVE_LOG_CRITICAL_TAG("Core", "Critical");

        WEAVE_LOG_CORE_TRACE("Trace");
        WEAVE_LOG_CORE_DEBUG("Debug");
        WEAVE_LOG_CORE_INFO("Info");
        WEAVE_LOG_CORE_WARN("Warn");
        WEAVE_LOG_CORE_ERROR("Error");
        WEAVE_LOG_CORE_CRITICAL("Critical");

        WEAVE_LOG_CORE_TRACE_TAG("Core", "Trace");
        WEAVE_LOG_CORE_DEBUG_TAG("Core", "Debug");
        WEAVE_LOG_CORE_INFO_TAG("Core", "Info");
        WEAVE_LOG_CORE_WARN_TAG("Core", "Warn");
        WEAVE_LOG_CORE_ERROR_TAG("Core", "Error");
        WEAVE_LOG_CORE_CRITICAL_TAG("Core", "Critical");

        Weave::KeyPressEvent keyPressEvent(WV_KEY_W, 1);
        WEAVE_LOG_INFO("{}", keyPressEvent.ToString());

        // CR_ASSERT(true, "True test");
        // CR_ASSERT(false, "False test {}", 3);
    }

    ~Sandbox() override = default;

    // void Run() override {}
};

std::unique_ptr<Weave::Application> Weave::CreateApplication(int argc, char** argv) {
    return std::make_unique<Sandbox>(argc, argv);
}
