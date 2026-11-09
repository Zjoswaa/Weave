#ifndef WEAVE_FRAMEBUFFER_RESIZE_EVENT_H
#define WEAVE_FRAMEBUFFER_RESIZE_EVENT_H

#include "weave/PCH.h"

#include "weave/core/events/event.h"

namespace Weave {
    class FramebufferResizeEvent final : public Event {
    public:
        FramebufferResizeEvent(const uint32_t width, const uint32_t height) {
            this->width = width;
            this->height = height;
        }

        [[nodiscard]] EventType get_type() const override {
            return get_static_type();
        }

        static EventType get_static_type() {
            return EventType::FramebufferResize;
        }

        [[nodiscard]] EventCategory get_categories() const override {
            return EventCategory::Application;
        }

        [[nodiscard]] const char* get_name() const override {
            return "FramebufferResizeEvent";
        }

        [[nodiscard]] std::string to_string() const override {
            std::stringstream ss;
            ss << "FramebufferResizeEvent { width: " << this->width << ", height: " <<  this->height << " }";
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
