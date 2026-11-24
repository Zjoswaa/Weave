#ifndef WEAVE_SANDBOX_LAYER_H
#define WEAVE_SANDBOX_LAYER_H

#include "weave/core/layer.h"
#include "weave/renderer/index_buffer.h"
#include "weave/renderer/vertex_buffer.h"

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
    unsigned int VAO = 0;
    std::unique_ptr<Weave::VertexBuffer> vertex_buffer;
    std::unique_ptr<Weave::IndexBuffer> index_buffer;
    unsigned int shader_program = 0;
};

#endif
