#ifndef WEAVE_OPENGL_IMGUI_LAYER_H
#define WEAVE_OPENGL_IMGUI_LAYER_H

#include "weave/imgui/imgui_layer.h"

namespace Weave {
    class OpenGlImGuiLayer : public ImGuiLayer {
    public:
        OpenGlImGuiLayer();
        ~OpenGlImGuiLayer() override = default;

        void on_attach() override;
        void on_detach() override;

        void begin() override;
        void end() override;
    };
}

#endif
