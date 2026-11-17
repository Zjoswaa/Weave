#ifndef WEAVE_KEY_TYPE_EVENT_H
#define WEAVE_KEY_TYPE_EVENT_H

#include "weave/core/events/event.h"
#include "weave/core/key_codes.h"

namespace Weave {
    class KeyTypeEvent final : public Event {
    public:
        KeyTypeEvent(const uint32_t codepoint) {
            this->codepoint = codepoint;
        }

        [[nodiscard]] EventType get_type() const override {
            return get_static_type();
        }

        static EventType get_static_type() {
            return EventType::KeyType;
        }

        [[nodiscard]] EventCategory get_categories() const override {
            return EventCategory::Input | EventCategory::Keyboard;
        }

        [[nodiscard]] const char* get_name() const override {
            return "KeyTypeEvent";
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "KeyTypeEvent { codepoint: " << this->codepoint << " }";
            return ss.str();
        }

        [[nodiscard]] inline uint32_t get_codepoint() const {
            return this->codepoint;
        }

    private:
        uint32_t codepoint;
    };
}

#endif
