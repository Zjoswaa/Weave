#include <weave.h>

class Sandbox : public Weave::Application {
public:
    Sandbox(const Weave::ApplicationSpecification& spec) : Application(spec) {
        WEAVE_LOG_INFO_TAG("Sandbox", "Sandbox::Sandbox()");
        // WEAVE_LOG_TRACE("Trace");
        // WEAVE_LOG_DEBUG("Debug");
        // WEAVE_LOG_INFO("Info");
        // WEAVE_LOG_WARN("Warn");
        // WEAVE_LOG_ERROR("Error");
        // WEAVE_LOG_CRITICAL("Critical");

        // WEAVE_LOG_TRACE_TAG("Core", "Trace");
        // WEAVE_LOG_DEBUG_TAG("Core", "Debug");
        // WEAVE_LOG_INFO_TAG("Core", "Info");
        // WEAVE_LOG_WARN_TAG("Core", "Warn");
        // WEAVE_LOG_ERROR_TAG("Core", "Error");
        // WEAVE_LOG_CRITICAL_TAG("Core", "Critical");

        // WEAVE_LOG_CORE_TRACE("Trace");
        // WEAVE_LOG_CORE_DEBUG("Debug");
        // WEAVE_LOG_CORE_INFO("Info");
        // WEAVE_LOG_CORE_WARN("Warn");
        // WEAVE_LOG_CORE_ERROR("Error");
        // WEAVE_LOG_CORE_CRITICAL("Critical");

        // WEAVE_LOG_CORE_TRACE_TAG("Core", "Trace");
        // WEAVE_LOG_CORE_DEBUG_TAG("Core", "Debug");
        // WEAVE_LOG_CORE_INFO_TAG("Core", "Info");
        // WEAVE_LOG_CORE_WARN_TAG("Core", "Warn");
        // WEAVE_LOG_CORE_ERROR_TAG("Core", "Error");
        // WEAVE_LOG_CORE_CRITICAL_TAG("Core", "Critical");
    }

    ~Sandbox() override = default;
};

std::unique_ptr<Weave::Application> Weave::create_application(int argc, char** argv) {
    WEAVE_LOG_INFO_TAG("Sandbox", "Weave::create_application()");

    ApplicationSpecification spec;
    spec.window_decorated = false;
    spec.window_fullscreen = false;
    spec.window_maximized = false;
    spec.window_resizable = false;

    return std::make_unique<Sandbox>(spec);
}
