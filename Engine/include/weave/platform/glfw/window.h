#ifndef WEAVE_GLFW_WINDOW_H
#define WEAVE_GLFW_WINDOW_H

#include "weave/core/window.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace Weave::GLFW {
    class Window : public Weave::Window {
    public:
        Window(const WindowSpecification& spec);
        ~Window() override;

        void init() override;
        void process_events() override;
        void swap_buffers() override;

        [[nodiscard]] uint32_t get_width() const override { return this->window_data.width; }
        [[nodiscard]] uint32_t get_height() const override { return this->window_data.height; }

        void set_event_callback(const std::function<void(Weave::Event&)>& callback) override { this->window_data.event_callback = callback; }

    private:
        void shutdown() const;

    private:
        GLFWwindow* window;
        WindowSpecification spec;

        struct WindowData {
            std::string title;
            uint32_t width, height;
            std::function<void(Weave::Event&)> event_callback;
            uint32_t key_repeat_counts[GLFW_KEY_LAST + 1] = {0};
            double last_mouse_x = 0;
            double last_mouse_y = 0;
        };

        WindowData window_data;
    };
}

#endif
