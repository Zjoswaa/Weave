#include "weave/core/application.h"
#include "weave/core/log.h"
#include "weave/core/window.h"

namespace Weave {
    Application::Application(const ApplicationSpecification& spec) {
        WEAVE_LOG_CORE_INFO_TAG("Application", "Application::Application()");

        this->spec = spec;

        WindowSpecification window_spec;
        window_spec.decorated = spec.window_decorated;
        window_spec.fullscreen = spec.window_fullscreen;
        window_spec.resizable = spec.window_resizable;
        this->window = Window::create(window_spec);
        this->window->init();
        this->window->set_event_callback([this](const Weave::Event& event) {
            this->on_event(event);
        });

        if (spec.window_maximized && !spec.window_fullscreen) {
            this->window->maximize();
        } else {
            // this->window->center();
        }
    };

    Application::~Application() = default;

    void Application::on_event(const Weave::Event& event) {
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
