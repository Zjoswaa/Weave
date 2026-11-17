#ifndef WEAVE_MOUSE_SCROLL_EVENT_H
#define WEAVE_MOUSE_SCROLL_EVENT_H

#include "weave/PCH.h"

#include "weave/core/events/event.h"

namespace Weave {
    class MouseScrollEvent final : public Event {
    public:
        MouseScrollEvent(const double x_offset, const double y_offset) {
            this->x_offset = x_offset;
            this->y_offset = y_offset;
        }

        [[nodiscard]] EventType get_type() const override {
            return get_static_type();
        }

        static EventType get_static_type() {
            return EventType::MouseScroll;
        }

        [[nodiscard]] EventCategory get_categories() const override {
            return EventCategory::Input | EventCategory::Mouse;
        }

        [[nodiscard]] const char* get_name() const override {
            return "MouseScrollEvent";
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "MouseScrollEvent { x_offset: " << this->x_offset << ", y_offset: " << this->y_offset << " }";
            return ss.str();
        }

        [[nodiscard]] inline double get_x_offset() const {
            return this->x_offset;
        }

        [[nodiscard]] inline double get_y_offset() const {
            return this->y_offset;
        }

    private:
        double x_offset;
        double y_offset;
    };
}

#endif
