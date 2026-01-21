#ifndef WEAVE_MOUSE_BUTTON_RELEASE_EVENT_H
#define WEAVE_MOUSE_BUTTON_RELEASE_EVENT_H

#include "Weave/PCH.h"

#include "Weave/Core/Events/Event.h"
#include "Weave/Core/KeyCodes.h"

namespace Weave {
    class MouseButtonReleaseEvent final : public Event {
    public:
        explicit MouseButtonReleaseEvent(const MouseButton mouseButton) {
            this->mouseButton = mouseButton;
        }

        [[nodiscard]] Type GetType() const override {
            return Type::MouseButtonRelease;
        }

        [[nodiscard]] uint32_t GetCategories() const override {
            return static_cast<uint32_t>(Category::Input) | static_cast<uint32_t>(Category::Mouse);
        }

        [[nodiscard]] const char* GetName() const override {
            return "MouseButtonReleaseEvent";
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleaseEvent { mouseButton: " << this->mouseButton << " }";
            return ss.str();
        }

        [[nodiscard]] inline MouseButton GetMouseButton() const {
            return this->mouseButton;
        }

    private:
        MouseButton mouseButton;
    };
}

#endif
