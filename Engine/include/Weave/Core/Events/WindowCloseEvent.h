#ifndef WEAVE_WINDOW_CLOSE_EVENT_H
#define WEAVE_WINDOW_CLOSE_EVENT_H

#include "Weave/Core/Events/Event.h"

namespace Weave {
    class WindowCloseEvent final : public Event {
    public:
        WindowCloseEvent() = default;

        [[nodiscard]] Type GetType() const override {
            return Type::WindowClose;
        }

        [[nodiscard]] uint32_t GetCategories() const override {
            return static_cast<uint32_t>(Category::Application);
        }

        [[nodiscard]] const char* GetName() const override {
            return "WindowCloseEvent";
        }
    };
}

#endif
