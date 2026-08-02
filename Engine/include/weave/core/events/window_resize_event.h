#ifndef WEAVE_WINDOW_RESIZE_EVENT_H
#define WEAVE_WINDOW_RESIZE_EVENT_H

#include "weave/PCH.h"

#include "weave/core/events/event.h"

namespace Weave {
    class WindowResizeEvent final : public Event {
    public:
        WindowResizeEvent(const uint32_t width, const uint32_t height) {
            this->width = width;
            this->height = height;
        }

        [[nodiscard]] EventType get_type() const override {
            return EventType::WindowResize;
        }

        [[nodiscard]] EventCategory get_categories() const override {
            return EventCategory::Application;
        }

        [[nodiscard]] const char* get_name() const override {
            return "WindowResizeEvent";
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent { width: " << this->width << ", height: " <<  this->height << " }";
            return ss.str();
        }

        [[nodiscard]] inline uint32_t get_width() const {
            return this->width;
        }

        [[nodiscard]] inline uint32_t get_height() const {
            return this->height;
        }

    private:
        uint32_t width;
        uint32_t height;
    };
}

#endif
