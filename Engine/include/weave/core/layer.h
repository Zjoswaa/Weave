#ifndef WEAVE_LAYER_H
#define WEAVE_LAYER_H

#include "weave/PCH.h"
#include "weave/core/events/event.h"

namespace Weave {
    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void on_attach() { }
        virtual void on_detach() { }
        virtual void on_update() { }
        virtual void on_event(Weave::Event& event) { }
        virtual void on_imgui_render() { }

        inline const std::string& get_name() { return name; }

    protected:
        std::string name;
    };
}

#endif
