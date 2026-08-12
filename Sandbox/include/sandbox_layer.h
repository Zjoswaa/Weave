#ifndef WEAVE_SANDBOX_LAYER_H
#define WEAVE_SANDBOX_LAYER_H

#include "weave/core/layer.h"

class SandboxLayer : public Weave::Layer {
public:
    SandboxLayer();
    virtual ~SandboxLayer() = default;

    void on_attach() override;
    void on_detach() override;
    void on_update() override;
    void on_event(Weave::Event& event) override;
    void on_imgui_render() override;

private:
    unsigned int VAO, VBO, shader_program = 0;
};

#endif
