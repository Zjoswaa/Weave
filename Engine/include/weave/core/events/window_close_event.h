#ifndef WEAVE_WINDOW_CLOSE_EVENT_H
#define WEAVE_WINDOW_CLOSE_EVENT_H

#include "weave/core/events/event.h"

namespace Weave {
    class WindowCloseEvent final : public Event {
    public:
        WindowCloseEvent() = default;

        [[nodiscard]] EventType get_type() const override {
            return EventType::WindowClose;
        }

        [[nodiscard]] EventCategory get_categories() const override {
            return EventCategory::Application;
        }

        [[nodiscard]] const char* get_name() const override {
            return "WindowCloseEvent";
        }
    };
}

#endif
