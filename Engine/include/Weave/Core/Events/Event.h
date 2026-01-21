#ifndef WEAVE_EVENT_H
#define WEAVE_EVENT_H

#include "Weave/PCH.h"

#include "Weave/Core/Core.h"

namespace Weave {
    class Event {
    public:
        enum class Type {
            None = 0,
            WindowClose,
            WindowResize,
            KeyPress,
            KeyRelease,
            MouseButtonPress,
            MouseButtonRelease,
            MouseMove
        };

        enum class Category : uint32_t {
            None = 0,
            Application = BIT(0),
            Input = BIT(1),
            Keyboard = BIT(2),
            Mouse = BIT(3)
        };

    public:
        virtual ~Event() = default;
        [[nodiscard]] virtual Type GetType() const = 0;
        [[nodiscard]] virtual uint32_t GetCategories() const = 0;
        [[nodiscard]] virtual const char* GetName() const = 0;
        [[nodiscard]] virtual std::string ToString() const { return GetName(); }

        [[nodiscard]] inline bool IsInCategory(Category category) const {
            return this->GetCategories() & static_cast<uint32_t>(category);
        }

    protected:
        bool handled = false;
    };
}

#endif
