#ifndef WEAVE_GLFW_WINDOW_H
#define WEAVE_GLFW_WINDOW_H

#include "weave/core/window.h"
#include "weave/renderer/graphics_context.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#ifdef WEAVE_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <dwmapi.h>
#endif

namespace Weave::GLFW {
    class Window : public Weave::Window {
    public:
        explicit Window(const WindowSpecification& spec);
        ~Window() override;

        bool init() override;
        void process_events() override;
        void swap_buffers() override;

        [[nodiscard]] uint32_t get_width() const override { return this->window_data.width; }
        [[nodiscard]] uint32_t get_height() const override { return this->window_data.height; }
        [[nodiscard]] uint32_t get_framebuffer_width() const override { return this->window_data.framebuffer_width; }
        [[nodiscard]] uint32_t get_framebuffer_height() const override { return this->window_data.framebuffer_height; }

        void maximize() const override;
        void center() const override;
        void set_resizable(bool resizable) const override;

        void set_event_callback(const std::function<void(Weave::Event&)>& callback) override {
            this->window_data.event_callback = callback;
        }

        /**
         * Get a reference to the underlying GLFWwindow.
         *
         * @return A pointer to the owned GLFWwindow.
         */
        [[nodiscard]] inline void* get_native_window() const override {
            return this->window;
        }

    private:
        void shutdown();

    private:
        GLFWwindow* window;
        std::unique_ptr<GraphicsContext> graphics_context;
        WindowSpecification spec;

        struct WindowData {
            std::string title;
            uint32_t width, height;
            uint32_t framebuffer_width, framebuffer_height;
            std::function<void(Weave::Event&)> event_callback;
            uint32_t key_repeat_counts[GLFW_KEY_LAST + 1] = {0};
            double last_mouse_x = 0;
            double last_mouse_y = 0;
            bool mouse_pos_valid = false;
        };

        WindowData window_data;
    };
}

#endif
