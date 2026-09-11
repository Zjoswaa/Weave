#include "weave/PCH.h"
#include "weave/core/application.h"
#include "weave/core/layer.h"
#include "weave/core/log.h"
#include "weave/core/window.h"
#include "weave/core/events/window_resize_event.h"
#include "weave/imgui/imgui_layer.h"
#include "weave/renderer/renderer.h"

#include <glad/glad.h>

namespace Weave {
    Application* Application::instance = nullptr;

    Application::Application(const ApplicationSpecification& spec) {
        instance = this;

        WEAVE_LOG_CORE_INFO_TAG("Application", "Application::Application()");

        this->spec = spec;

        WindowSpecification window_spec;
        window_spec.decorated = spec.window_decorated;
        window_spec.fullscreen = spec.window_fullscreen;
        window_spec.resizable = spec.window_resizable;
        this->window = Window::create(window_spec);
        this->window->set_event_callback([this](Weave::Event& event) {
            this->on_event(event);
        });
        this->window->init();

        if (spec.window_maximized && !spec.window_fullscreen) {
            this->window->maximize();
        } else {
            // this->window->center();
        }

        this->imgui_layer = ImGuiLayer::create();
        this->push_overlay(this->imgui_layer);
    };

    Application::~Application() {
        WEAVE_LOG_CORE_INFO_TAG("Application", "Application::~Application()");

        for (Layer* layer : layer_stack) {
            layer->on_detach();
            delete layer;
        }

        // delete this->imgui_layer;
    };

    void Application::on_event(Weave::Event& event) {
        WEAVE_LOG_CORE_TRACE_TAG("Event", "{}", event.to_string());

        if (event.get_type() == EventType::WindowClose) {
            this->running = false;
        }

        for (const auto & it : std::views::reverse(this->layer_stack)) {
            it->on_event(event);
            if (event.handled) {
                break;
            }
        }
    }

    void Application::push_layer(Layer* layer) {
        this->layer_stack.push(layer);
        layer->on_attach();
    }

    void Application::push_overlay(Layer* layer) {
        this->layer_stack.push_overlay(layer);
        layer->on_attach();
    }

    void Application::pop_layer(Layer* layer) {
        this->layer_stack.pop(layer);
        layer->on_detach();
    }

    void Application::pop_overlay(Layer* layer) {
        this->layer_stack.pop_overlay(layer);
        layer->on_detach();
    }

    void Application::run() {
        WEAVE_LOG_CORE_INFO_TAG("Application", "Application::run()");

        while(this->running) {
            // Cornflower blue
            Renderer::set_clear_color(0.38823529f, 0.58431372f, 0.93333333f, 1.0f);
            //Renderer::set_clear_color(0.2f, 0.2f, 0.2f, 1.0f);
            Renderer::clear();

            for (Layer* layer : this->layer_stack) {
                layer->on_update();
            }

            this->imgui_layer->begin();
            for (Layer* layer : this->layer_stack) {
                layer->on_imgui_render();
            }
            this->imgui_layer->end();

            this->window->process_events();
            this->window->swap_buffers();
        }

        WEAVE_LOG_CORE_INFO_TAG("Application", "Exiting application.");
    }

    void Application::close() {
        this->running = false;
    }
}
