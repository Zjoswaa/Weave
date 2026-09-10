#ifndef WEAVE_SANDBOX_LAYER_H
#define WEAVE_SANDBOX_LAYER_H

#include "weave/core/layer.h"
#include "weave/renderer/buffer_layout.h"
#include "weave/renderer/vertex_array.h"
#include "weave/renderer/vertex_buffer.h"
#include "weave/renderer/index_buffer.h"
#include "weave/renderer/renderer.h"
#include "weave/renderer/shader.h"

#include <memory>

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
    std::shared_ptr<Weave::Shader> shader;
    std::shared_ptr<Weave::VertexBuffer> vertex_buffer;
    std::shared_ptr<Weave::IndexBuffer> index_buffer;
    std::shared_ptr<Weave::VertexArray> vertex_array;
    unsigned int VAO;
};

#endif
