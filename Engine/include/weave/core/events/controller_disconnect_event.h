#ifndef WEAVE_CONTROLLER_DISCONNECT_EVENT_H
#define WEAVE_CONTROLLER_DISCONNECT_EVENT_H

#include "weave/PCH.h"

#include "weave/core/events/event.h"

namespace Weave {
    class ControllerDisconnectEvent final : public Event {
    public:
        ControllerDisconnectEvent(const std::string& controller_name) {
            this->controller_name = controller_name;
        }

        [[nodiscard]] EventType get_type() const override {
            return get_static_type();
        }

        static EventType get_static_type() {
            return EventType::ControllerDisconnect;
        }

        [[nodiscard]] EventCategory get_categories() const override {
            return EventCategory::Input | EventCategory::Controller;
        }

        [[nodiscard]] const char* get_name() const override {
            return "ControllerDisconnectEvent";
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "ControllerDisconnectEvent { controller_name: " << this->controller_name << " }";
            return ss.str();
        }

        [[nodiscard]] inline const std::string& get_controller_name() const {
            return this->controller_name;
        }

    private:
        std::string controller_name;
    };
}

#endif
