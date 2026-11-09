#ifndef WEAVE_WINDOW_H
#define WEAVE_WINDOW_H

#include "weave/PCH.h"
#include "weave/core/events/event.h"

namespace Weave {
    struct WindowSpecification {
        std::string title = "Window";
        uint32_t width = 1280;
        uint32_t height = 720;
        bool decorated = true;
        bool fullscreen = false;
        bool resizable = true;
    };

    class Window {
    public:
        Window() = default;
        virtual ~Window() = default;

        virtual bool init() = 0;
        virtual void process_events() = 0;
        virtual void swap_buffers() = 0;

        [[nodiscard]] virtual uint32_t get_width() const = 0;
        [[nodiscard]] virtual uint32_t get_height() const = 0;
        [[nodiscard]] virtual uint32_t get_framebuffer_width() const = 0;
        [[nodiscard]] virtual uint32_t get_framebuffer_height() const = 0;

        virtual void maximize() const = 0;
        virtual void center() const = 0;
        virtual void set_resizable(bool resizable) const = 0;

        virtual void set_event_callback(const std::function<void(Weave::Event&)>& callback) = 0;

        [[nodiscard]] virtual void* get_native_window() const = 0;

        static std::unique_ptr<Window> create(const WindowSpecification& spec = WindowSpecification());

        // Remove copy and move constructors
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;
    };
}

#endif
