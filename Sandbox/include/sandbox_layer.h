#ifndef WEAVE_SANDBOX_LAYER_H
#define WEAVE_SANDBOX_LAYER_H

#include "weave/core/layer.h"
#include "weave/renderer/buffer_layout.h"
#include "weave/renderer/camera.h"
#include "weave/renderer/framebuffer.h"
#include "weave/renderer/index_buffer.h"
#include "weave/renderer/renderer.h"
#include "weave/renderer/shader.h"
#include "weave/renderer/vertex_array.h"
#include "weave/renderer/vertex_buffer.h"

#include <imgui.h>

#include <memory>

class SandboxLayer : public Weave::Layer {
public:
    SandboxLayer();
    virtual ~SandboxLayer() = default;

    void on_attach() override;
    // void on_detach() override;
    void on_update() override;
    void on_event(Weave::Event& event) override;
    void on_imgui_render() override;

private:
    std::shared_ptr<Weave::Shader> shader;
    std::shared_ptr<Weave::VertexBuffer> vertex_buffer;
    std::shared_ptr<Weave::IndexBuffer> index_buffer;
    std::shared_ptr<Weave::VertexArray> vertex_array;
    std::shared_ptr<Weave::Framebuffer> framebuffer;

    Weave::Camera camera;
    glm::vec3 camera_position{0.0f, 0.0f, 1.0f};

    void render_dockspace();
    void render_menu_bar();
    void render_viewport();
    void render_scene();
    void render_settings();
    void render_about_menu();

    uint32_t load_texture_from_file(const char* path);

    bool opt_fullscreen = true;
    bool dockspace_open = true;
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    uint32_t menu_icon_id = 0;
    uint32_t icon_min_id = 0;
    uint32_t icon_max_id = 0;
    uint32_t icon_close_id = 0;
    bool show_about_menu = false;
};

#endif
