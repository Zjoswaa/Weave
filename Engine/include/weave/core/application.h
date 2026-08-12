#ifndef WEAVE_APPLICATION_H
#define WEAVE_APPLICATION_H

#include "weave/PCH.h"
#include "weave/core/layer.h"
#include "weave/core/layer_stack.h"
#include "weave/core/window.h"
#include "weave/imgui/imgui_layer.h"

namespace Weave {
    struct ApplicationSpecification {
        std::string name = "Application";
        uint32_t window_width = 1280;
        uint32_t window_height = 720;
        bool window_decorated = false;
        bool window_fullscreen = false;
        bool window_maximized = false;
        bool window_resizable = true;
    };

    class Application {
    public:
        Application(const ApplicationSpecification& spec);
        virtual ~Application();

        void run();

        virtual void on_event(Weave::Event& event);

        void push_layer(Layer* layer);
        void push_overlay(Layer* layer);
        void pop_layer(Layer* layer);
        void pop_overlay(Layer* layer);

        inline Window& get_window() { return *this->window; }
        static inline Application& get() { return *instance; }

    private:
        ApplicationSpecification spec;
        std::unique_ptr<Window> window;
        bool running = true;
        LayerStack layer_stack;
        ImGuiLayer* imgui_layer;

        static Application* instance;
    };

    // Implemented by client
    std::unique_ptr<Application> create_application(int argc, char** argv);
}

#endif
