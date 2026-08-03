#ifndef WEAVE_GLFW_WINDOW_H
#define WEAVE_GLFW_WINDOW_H

#include "weave/core/window.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace Weave {
    class GlfwWindow : public Window {
    public:
        GlfwWindow(const WindowSpecification& spec);
        virtual ~GlfwWindow();

        void init() override;
        void process_events() override;
        void swap_buffers() override;

        uint32_t get_width() const override { return this->window_data.width; }
        uint32_t get_height() const override { return this->window_data.height; }

        void set_event_callback(const std::function<void(Weave::Event&)>& callback) override { this->window_data.event_callback = callback; }

        // void set_vsync(bool enabled) override;
        // bool is_vsync() const override;

    private:
        virtual void shutdown();

    private:
        GLFWwindow* window;
        WindowSpecification spec;

        struct WindowData {
            std::string title;
            uint32_t width, height;
            // bool vsync;
            std::function<void(Weave::Event&)> event_callback;
            uint32_t key_repeat_counts[GLFW_KEY_LAST + 1] = {0};
        };

        WindowData window_data;
    };
}

#endif
