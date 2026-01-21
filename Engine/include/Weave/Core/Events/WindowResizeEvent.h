#ifndef WEAVE_WINDOW_RESIZE_EVENT_H
#define WEAVE_WINDOW_RESIZE_EVENT_H

#include "Weave/PCH.h"

#include "Weave/Core/Events/Event.h"

namespace Weave {
    class WindowResizeEvent final : public Event {
    public:
        WindowResizeEvent(const uint32_t width, const uint32_t height) {
            this->width = width;
            this->height = height;
        }

        [[nodiscard]] Type GetType() const override {
            return Type::WindowResize;
        }

        [[nodiscard]] uint32_t GetCategories() const override {
            return static_cast<uint32_t>(Category::Application);
        }

        [[nodiscard]] const char* GetName() const override {
            return "WindowResizeEvent";
        }

        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent { width: " << this->width << ", height: " <<  this->height << " }";
            return ss.str();
        }

        [[nodiscard]] inline uint32_t GetWidth() const {
            return this->width;
        }

        [[nodiscard]] inline uint32_t GetHeight() const {
            return this->height;
        }

    private:
        uint32_t width;
        uint32_t height;
    };
}

#endif
