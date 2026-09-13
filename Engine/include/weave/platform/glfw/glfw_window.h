#ifndef WEAVE_GLFW_WINDOW_H
#define WEAVE_GLFW_WINDOW_H

#include "weave/core/window.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "weave/renderer/graphics_context.h"

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
        uint32_t get_framebuffer_width() const override;
        uint32_t get_framebuffer_height() const override;
        void set_refresh_callback(const std::function<void()>& callback) override {
            this->window_data.refresh_callback = callback;
        }
        void refresh();
        bool owns_native_resize_cursor() const override;

        void maximize() const override;
        bool is_maximized() const override;
        void minimize() const override;
        void restore() const override;
        void center() const override;
        void set_resizable(bool resizable) const override;
        void set_title_bar_drag_offset(int32_t left, int32_t right);
        inline int32_t get_title_bar_drag_offset_left() const override {
            return this->window_data.title_bar_drag_offset_left;
        }
        inline int32_t get_title_bar_drag_offset_right() const override {
            return this->window_data.title_bar_drag_offset_right;
        }

        void set_event_callback(const std::function<void(Weave::Event&)>& callback) override {
            this->window_data.event_callback = callback;
        }

        inline void* get_native_window() const override { return this->window; }

        // void set_vsync(bool enabled) override;
        // bool is_vsync() const override;

    private:
        virtual void shutdown();

    private:
        GLFWwindow* window;
        std::unique_ptr<GraphicsContext> graphics_context;
        WindowSpecification spec;

        struct WindowData {
            std::string title;
            uint32_t width, height;
            int32_t title_bar_drag_offset_left = 0;
            int32_t title_bar_drag_offset_right = 0;
            // bool vsync;
            std::function<void(Weave::Event&)> event_callback;
            std::function<void()> refresh_callback;
            uint32_t key_repeat_counts[GLFW_KEY_LAST + 1] = {0};
            double last_mouse_x = 0;
            double last_mouse_y = 0;
        };

        WindowData window_data;
    };
} // namespace Weave

#endif
