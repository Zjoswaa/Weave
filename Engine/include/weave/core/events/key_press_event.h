#ifndef WEAVE_KEY_PRESS_EVENT_H
#define WEAVE_KEY_PRESS_EVENT_H

#include "weave/core/events/event.h"
#include "weave/core/key_codes.h"

namespace Weave {
    class KeyPressEvent final : public Event {
    public:
        KeyPressEvent(const KeyCode key_code, const uint32_t repeat_count) {
            this->key_code = key_code;
            this->repeat_count = repeat_count;
        }

        [[nodiscard]] EventType get_type() const override {
            return EventType::KeyPress;
        }

        [[nodiscard]] EventCategory get_categories() const override {
            return EventCategory::Input | EventCategory::Keyboard;
        }

        [[nodiscard]] const char* get_name() const override {
            return "KeyPressEvent";
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "KeyPressEvent { key_code: " << this->key_code << ", repeat_count: " << this->repeat_count << " }";
            return ss.str();
        }

        [[nodiscard]] inline KeyCode get_key_code() const {
            return this->key_code;
        }

        [[nodiscard]] inline uint32_t get_repeat_count() const {
            return this->repeat_count;
        }

    private:
        KeyCode key_code;
        uint32_t repeat_count;
    };
}

#endif
