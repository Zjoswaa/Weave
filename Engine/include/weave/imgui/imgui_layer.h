#ifndef WEAVE_IMGUI_LAYER_H
#define WEAVE_IMGUI_LAYER_H

#include "weave/core/layer.h"

namespace Weave {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer() : Layer("ImGuiLayer") { }
        virtual ~ImGuiLayer() = default;

        virtual void begin() = 0;
        virtual void end() = 0;

        void set_custom_dark_theme();
        void set_custom_style();

        static ImGuiLayer* create();
    };
}

#endif
