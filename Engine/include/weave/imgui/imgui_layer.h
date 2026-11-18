#ifndef WEAVE_IMGUI_LAYER_H
#define WEAVE_IMGUI_LAYER_H

#include "weave/core/layer.h"
#include "weave/core/events/event.h"
#include "weave/core/events/key_press_event.h"
#include "weave/core/events/key_release_event.h"
#include "weave/core/events/key_type_event.h"
#include "weave/core/events/mouse_button_press_event.h"
#include "weave/core/events/mouse_button_release_event.h"
#include "weave/core/events/mouse_move_event.h"
#include "weave/core/events/mouse_scroll_event.h"
#include "weave/core/events/window_resize_event.h"

namespace Weave {
    class ImGuiLayer : public Weave::Layer {
    public:
        ImGuiLayer() : Weave::Layer("ImGuiLayer") { }
        virtual ~ImGuiLayer() = default;

        virtual void begin() = 0;
        virtual void end() = 0;

        void set_custom_dark_theme();
        void set_custom_style();

        static ImGuiLayer* create();
    };
}

#endif
