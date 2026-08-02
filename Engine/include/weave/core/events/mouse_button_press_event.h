#ifndef WEAVE_MOUSE_BUTTON_PRESS_EVENT_H
#define WEAVE_MOUSE_BUTTON_PRESS_EVENT_H

#include "weave/PCH.h"

#include "weave/core/events/event.h"
#include "weave/core/key_codes.h"

namespace Weave {
    class MouseButtonPressEvent final : public Event {
    public:
        explicit MouseButtonPressEvent(const MouseButton mouse_button) {
            this->mouse_button = mouse_button;
        }

        [[nodiscard]] EventType get_type() const override {
            return EventType::MouseButtonPress;
        }

        [[nodiscard]] EventCategory get_categories() const override {
            return EventCategory::Input | EventCategory::Mouse;
        }

        [[nodiscard]] const char* get_name() const override {
            return "MouseButtonPressEvent";
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "MouseButtonPressEvent { mouse_button: " << this->mouse_button << " }";
            return ss.str();
        }

        [[nodiscard]] inline MouseButton get_mouse_button() const {
            return this->mouse_button;
        }

    private:
        MouseButton mouse_button;
    };
}

#endif
