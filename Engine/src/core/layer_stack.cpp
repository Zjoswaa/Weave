#include "weave/PCH.h"
#include "weave/core/layer_stack.h"

namespace Weave {
    void LayerStack::push(Weave::Layer* layer) {
        this->layers.emplace(this->layers.begin() + insert_index, layer);
        insert_index++;
    }

    void LayerStack::push_overlay(Weave::Layer* layer) {
        this->layers.emplace_back(layer);
    }

    void LayerStack::pop(Weave::Layer* layer) {
        auto it = std::find(this->layers.begin(), this->layers.begin() + this->insert_index, layer);

        if (it != this->layers.begin() + this->insert_index) {
            this->layers.erase(it);
            this->insert_index--;
        }
    }

    void LayerStack::pop_overlay(Weave::Layer* layer) {
        auto it = std::find(this->layers.begin() + this->insert_index, this->layers.end(), layer);

        if (it != this->layers.end()) {
            this->layers.erase(it);
        }
    }
}
