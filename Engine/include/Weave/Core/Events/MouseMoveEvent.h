#ifndef WEAVE_MOUSE_MOVE_EVENT_H
#define WEAVE_MOUSE_MOVE_EVENT_H

#include "Weave/PCH.h"

#include "Weave/Core/Events/Event.h"

namespace Weave {
    class MouseMoveEvent final : public Event {
    public:
        MouseMoveEvent(const float x, const float y, const float deltaX, const float deltaY) {
            this->x = x;
            this->y = y;
            this->deltaX = deltaX;
            this->deltaY = deltaY;
        }

        [[nodiscard]] Type GetType() const override {
            return Type::MouseMove;
        }

        [[nodiscard]] uint32_t GetCategories() const override {
            return static_cast<uint32_t>(Category::Input) | static_cast<uint32_t>(Category::Mouse);
        }

        [[nodiscard]] const char* GetName() const override {
            return "MouseMoveEvent";
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMoveEvent { x: " << this->x << ", y: " << this->y << ", deltaX: " << this->deltaX << ", deltaY: " << this->deltaY << " }";
            return ss.str();
        }

    private:
        float x;
        float y;
        float deltaX;
        float deltaY;
    };
}

#endif
