#ifndef WEAVE_EVENT_H
#define WEAVE_EVENT_H

#include "weave/PCH.h"

#include "weave/core/core.h"

namespace Weave {
    enum class EventType {
        None = 0,
        WindowClose,
        WindowResize,
        FramebufferResize,
        KeyPress,
        KeyRelease,
        MouseButtonPress,
        MouseButtonRelease,
        MouseMove
    };

    enum class EventCategory : uint32_t {
        None = 0,
        Application = BIT(0),
        Input = BIT(1),
        Keyboard = BIT(2),
        Mouse = BIT(3)
    };

    [[nodiscard]] constexpr EventCategory operator|(EventCategory lhs, EventCategory rhs) {
        return static_cast<EventCategory>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
    }
    [[nodiscard]] constexpr EventCategory operator&(EventCategory lhs, EventCategory rhs) {
        return static_cast<EventCategory>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
    }

    class Event {
    public:
        virtual ~Event() = default;
        [[nodiscard]] virtual EventType get_type() const = 0;
        [[nodiscard]] virtual EventCategory get_categories() const = 0;
        [[nodiscard]] virtual const char* get_name() const = 0;
        [[nodiscard]] virtual std::string to_string() const { return get_name(); }

        [[nodiscard]] inline bool is_in_category(EventCategory category) const {
            return (this->get_categories() & category) != EventCategory::None;
        }

        bool handled = false;
    };

    class EventDispatcher {
    public:
        explicit EventDispatcher(Event &event) : event(event) {}

        template <typename T, typename F>
        bool dispatch(const F &handler) {
            if (event.get_type() == T::get_static_type()) {
                event.handled |= handler(static_cast<T &>(event));
                return true;
            }
            return false;
        }

    private:
        Event &event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.to_string();
    }
}

#endif
