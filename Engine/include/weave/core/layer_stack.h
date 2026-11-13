#ifndef WEAVE_LAYER_STACK_H
#define WEAVE_LAYER_STACK_H

#include "weave/PCH.h"
#include "weave/core/layer.h"

namespace Weave {
    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack() = default;

        void push(Weave::Layer* layer);
        void push_overlay(Weave::Layer* layer);
        void pop(Weave::Layer* layer);
        void pop_overlay(Weave::Layer* layer);

        std::vector<Layer*>::iterator begin() { return layers.begin(); }
        std::vector<Layer*>::iterator end() { return layers.end(); }
        // std::vector<Layer*>::reverse_iterator rbegin() { return layers.rbegin(); }
        // std::vector<Layer*>::reverse_iterator rend() { return layers.rend(); }

    private:
        std::vector<Weave::Layer*> layers;
        uint32_t insert_index = 0;
    };
}

#endif
