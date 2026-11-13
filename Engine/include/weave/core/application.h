#ifndef WEAVE_APPLICATION_H
#define WEAVE_APPLICATION_H

#include "weave/PCH.h"
#include "weave/core/events/event.h"
#include "weave/core/layer.h"
#include "weave/core/layer_stack.h"
#include "weave/core/window.h"
#include "weave/imgui/imgui_layer.h"
#include "weave/platform/platform.h"

namespace Weave {
    struct ApplicationSpecification {
        std::string name = "Application";
        uint32_t window_width = 1280;
        uint32_t window_height = 720;
        bool window_decorated = true;
        bool window_fullscreen = false;
        bool window_maximized = false;
        bool window_resizable = true;
    };

    class Application {
    public:
        Application(const ApplicationSpecification& spec);
        virtual ~Application();

        virtual void run();
        virtual void on_event(Weave::Event& event);

        void push_layer(Layer* layer);
        void push_overlay(Layer* layer);
        void pop_layer(Layer* layer);
        void pop_overlay(Layer* layer);

        inline Window& get_window() const { return *this->window; }
        static inline Application& get() { return *instance; }

    private:
        bool running = false;
        ApplicationSpecification spec;

        std::unique_ptr<Weave::Platform> platform;
        std::unique_ptr<Weave::Window> window;
        ImGuiLayer* imgui_layer;
        LayerStack layer_stack;

        static Application* instance;
    };

    // Implemented by client
    std::unique_ptr<Application> create_application(int argc, char** argv);
}

#endif
