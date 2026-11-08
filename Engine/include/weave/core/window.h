#ifndef WEAVE_WINDOW_H
#define WEAVE_WINDOW_H

#include "weave/PCH.h"
#include "weave/core/events/event.h"

namespace Weave {
    struct WindowSpecification {
        std::string title = "Window";
        uint32_t width = 1280;
        uint32_t height = 720;
        bool fullscreen = false;
    };

    class Window {
    public:
        virtual ~Window() = default;

        virtual void init() = 0;
        virtual void process_events() = 0;
        virtual void swap_buffers() = 0;

        [[nodiscard]] virtual uint32_t get_width() const = 0;
        [[nodiscard]] virtual uint32_t get_height() const = 0;

        virtual void set_event_callback(const std::function<void(Weave::Event&)>& callback) = 0;

        static std::unique_ptr<Window> create(const WindowSpecification& spec = WindowSpecification());
    };
}

#endif
