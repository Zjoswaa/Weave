#include "weave/core/application.h"
#include "weave/core/log.h"
#include "weave/core/window.h"

namespace Weave {
    Application::Application() {
        WEAVE_LOG_CORE_INFO_TAG("Application", "Application::Application()");

        WindowSpecification window_spec;
        this->window = Window::create(window_spec);
        this->window->init();
        this->window->set_event_callback([this](Weave::Event& event) {
            this->on_event(event);
        });
    };


    Application::~Application() = default;

    void Application::on_event(Weave::Event& event) {
        WEAVE_LOG_CORE_INFO_TAG("Event", "{}", event.to_string());

        if (event.get_type() == EventType::WindowClose) {
            WEAVE_LOG_CORE_INFO_TAG("Application", "Exiting application.");
            this->running = false;
        }
    }

    void Application::run() {
        WEAVE_LOG_CORE_INFO_TAG("Application", "Application::run()");

        while(this->running) {
            this->window->process_events();
            this->window->swap_buffers();
        }
    }
}
