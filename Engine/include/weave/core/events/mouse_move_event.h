#ifndef WEAVE_MOUSE_MOVE_EVENT_H
#define WEAVE_MOUSE_MOVE_EVENT_H

#include "weave/PCH.h"

#include "weave/core/events/event.h"

namespace Weave {
    class MouseMoveEvent final : public Event {
    public:
        MouseMoveEvent(const double x, const double y, const double delta_x, const double delta_y) {
            this->x = x;
            this->y = y;
            this->delta_x = delta_x;
            this->delta_y = delta_y;
        }

        [[nodiscard]] EventType get_type() const override {
            return EventType::MouseMove;
        }

        [[nodiscard]] EventCategory get_categories() const override {
            return EventCategory::Input | EventCategory::Mouse;
        }

        [[nodiscard]] const char* get_name() const override {
            return "MouseMoveEvent";
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "MouseMoveEvent { x: " << this->x << ", y: " << this->y << ", delta_x: " << this->delta_x << ", delta_y: " << this->delta_y << " }";
            return ss.str();
        }

    private:
        double x;
        double y;
        double delta_x;
        double delta_y;
    };
}

#endif
