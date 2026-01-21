#ifndef WEAVE_KEY_RELEASE_EVENT_H
#define WEAVE_KEY_RELEASE_EVENT_H

#include "Weave/Core/Events/Event.h"
#include "Weave/Core/KeyCodes.h"

namespace Weave {
    class KeyReleaseEvent final : public Event {
    public:
        explicit KeyReleaseEvent(const KeyCode keyCode) {
            this->keyCode = keyCode;
        }

        [[nodiscard]] Type GetType() const override {
            return Type::KeyRelease;
        }

        [[nodiscard]] uint32_t GetCategories() const override {
            return static_cast<uint32_t>(Category::Input) | static_cast<uint32_t>(Category::Keyboard);
        }

        [[nodiscard]] const char* GetName() const override {
            return "KeyReleaseEvent";
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent { keyCode: " << this->keyCode << " }";
            return ss.str();
        }

        [[nodiscard]] KeyCode GetKeyCode() const {
            return this->keyCode;
        }

    private:
        KeyCode keyCode;
    };
}

#endif
