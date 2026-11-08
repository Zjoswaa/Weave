#ifndef WEAVE_KEY_RELEASE_EVENT_H
#define WEAVE_KEY_RELEASE_EVENT_H

#include "weave/core/events/event.h"
#include "weave/core/key_codes.h"

namespace Weave {
    class KeyReleaseEvent final : public Event {
    public:
        explicit KeyReleaseEvent(const KeyCode key_code) {
            this->key_code = key_code;
        }

        [[nodiscard]] EventType get_type() const override {
            return EventType::KeyRelease;
        }

        [[nodiscard]] EventCategory get_categories() const override {
            return EventCategory::Input | EventCategory::Keyboard;
        }

        [[nodiscard]] const char* get_name() const override {
            return "KeyReleaseEvent";
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "KeyReleaseEvent { key_code: " << this->key_code << " }";
            return ss.str();
        }

        [[nodiscard]] KeyCode get_key_code() const {
            return this->key_code;
        }

    private:
        KeyCode key_code;
    };
}

#endif
