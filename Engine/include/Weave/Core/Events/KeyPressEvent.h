#ifndef WEAVE_KEY_PRESS_EVENT_H
#define WEAVE_KEY_PRESS_EVENT_H

#include "Weave/Core/Events/Event.h"
#include "Weave/Core/KeyCodes.h"

namespace Weave {
    class KeyPressEvent final : public Event {
    public:
        KeyPressEvent(const KeyCode keyCode, const uint32_t repeatCount) {
            this->keyCode = keyCode;
            this->repeatCount = repeatCount;
        }

        [[nodiscard]] Type GetType() const override {
            return Type::KeyPress;
        }

        [[nodiscard]] uint32_t GetCategories() const override {
            return static_cast<uint32_t>(Category::Input) | static_cast<uint32_t>(Category::Keyboard);
        }

        [[nodiscard]] const char* GetName() const override {
            return "KeyPressEvent";
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent { keyCode: " << this->keyCode << ", repeatCount: " << this->repeatCount << " }";
            return ss.str();
        }

        [[nodiscard]] inline KeyCode GetKeyCode() const {
            return this->keyCode;
        }

        [[nodiscard]] inline uint32_t GetRepeatCount() const {
            return this->repeatCount;
        }

    private:
        KeyCode keyCode;
        uint32_t repeatCount;
    };
}

#endif
