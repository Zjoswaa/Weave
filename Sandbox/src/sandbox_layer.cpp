#include "sandbox_layer.h"
#include "weave/core/application.h"
#include "weave/core/log.h"
#include "weave/core/version.h"
#include "weave/renderer/renderer.h"

#include <cmath>
#include <glad/glad.h>
#include <imgui.h>
#include <limits>
#include <stb_image.h>
// #include "weave/core/log.h"

SandboxLayer::SandboxLayer() : Layer("SandboxLayer") {}

void SandboxLayer::on_attach() {
    this->menu_icon_id =
        this->load_texture_from_file((std::filesystem::path(ASSETS_DIR) / "icons" / "W_32.png").string().c_str());
    this->icon_min_id =
        this->load_texture_from_file((std::filesystem::path(ASSETS_DIR) / "icons" / "minimize.png").string().c_str());
    this->icon_max_id =
        this->load_texture_from_file((std::filesystem::path(ASSETS_DIR) / "icons" / "maximize.png").string().c_str());
    this->icon_close_id =
        this->load_texture_from_file((std::filesystem::path(ASSETS_DIR) / "icons" / "close.png").string().c_str());

    Weave::FramebufferSpecification framebuffer_spec;
    framebuffer_spec.width = 1280;
    framebuffer_spec.height = 720;
    this->framebuffer = Weave::Framebuffer::create(framebuffer_spec);

    this->vertex_array.reset(Weave::VertexArray::create());

    float vertices[] = {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f,
                        0.0f,  1.0f,  0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f,  1.0f};

    this->vertex_buffer.reset(Weave::VertexBuffer::create(vertices, sizeof(vertices)));

    Weave::BufferLayout layout = {{Weave::ShaderDataType::Float3, "aPos"}, {Weave::ShaderDataType::Float3, "color"}};
    this->vertex_buffer->set_layout(layout);
    this->vertex_array->add_vertex_buffer(this->vertex_buffer);

    uint32_t indices[] = {0, 1, 2};
    this->index_buffer.reset(Weave::IndexBuffer::create(indices, 3));
    this->vertex_array->set_index_buffer(this->index_buffer);

    const char* vertex_shader_source = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 color;

        uniform mat4 uViewProjection;

        out vec3 vertexColor;
        void main() {
            gl_Position = uViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
            vertexColor = color;
        }
    )";

    const char* fragment_shader_source = R"(
        #version 330 core
        out vec4 FragColor;
        in vec3 vertexColor;
        void main() {
            FragColor = vec4(vertexColor, 1.0f);
        }
    )";

    this->shader.reset(Weave::Shader::create(vertex_shader_source, fragment_shader_source));

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void SandboxLayer::on_update() { this->camera.set_position(this->camera_position); }

void SandboxLayer::render_scene() {
    this->framebuffer->bind();

    Weave::Renderer::set_clear_color(0.2f, 0.2f, 0.2f, 1.0f);
    Weave::Renderer::clear();

    this->shader->bind();
    this->shader->set_mat4("uViewProjection", this->camera.get_view_projection_matrix());
    Weave::Renderer::draw_indexed(this->vertex_array);

    this->framebuffer->unbind();
}

void SandboxLayer::on_event(Weave::Event& event) {
    // WEAVE_LOG_INFO_TAG("Sandbox Layer", "{}", event.to_string());
}

void SandboxLayer::on_imgui_render() {
    this->render_dockspace();
    this->render_viewport();
    this->render_settings();

    ImGui::ShowDemoWindow();

    if (this->show_about_menu) {
        this->render_about_menu();
    }

    ImGui::End();
}

void SandboxLayer::render_dockspace() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    if (this->opt_fullscreen) {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 8.f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);

    ImGui::Begin("DockSpace", &this->dockspace_open, window_flags);

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar();

    if (this->opt_fullscreen) {
        ImGui::PopStyleVar(2);
    }

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("DockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), this->dockspace_flags);
    }

    this->render_menu_bar();
}

void SandboxLayer::render_menu_bar() {
    if (ImGui::BeginMenuBar()) {
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.0f);
        if (this->menu_icon_id) {
            ImTextureID icon_tex_id = (ImTextureID)(intptr_t)this->menu_icon_id;
            ImGui::Image(icon_tex_id, ImVec2(24.0f, 24.0f), ImVec2(0, 1), ImVec2(1, 0));
        }

        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New")) {
            }
            if (ImGui::MenuItem("Open")) {
            }
            if (ImGui::BeginMenu("Open Recent")) {
                ImGui::MenuItem("fish_hat.c");
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save As..")) {
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit")) {
                Weave::Application::get().close();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About")) {
                this->show_about_menu = true;
            }
            ImGui::EndMenu();
        }

        Weave::Application::get().get_window().set_title_bar_drag_offset((int32_t)ImGui::GetCursorPosX(), 130);

        float icon_size = 20.0f;

        float button_width = icon_size + (ImGui::GetStyle().FramePadding.x * 2.0f);
        float item_spacing = ImGui::GetStyle().ItemSpacing.x;
        float total_width_needed = (button_width * 3) + (item_spacing * 2);

        ImGui::SetCursorPosX(ImGui::GetWindowWidth() - total_width_needed - 6.f);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);

        ImTextureID min_tex_id = (ImTextureID)(intptr_t)this->icon_min_id;
        if (ImGui::ImageButton("##min", min_tex_id, ImVec2(icon_size, icon_size), ImVec2(0, 1), ImVec2(1, 0))) {
            Weave::Application::get().get_window().minimize();
        }
        ImGui::SameLine();

        ImTextureID max_tex_id = (ImTextureID)(intptr_t)this->icon_max_id;
        if (ImGui::ImageButton("##max", max_tex_id, ImVec2(icon_size, icon_size), ImVec2(0, 1), ImVec2(1, 0))) {
            Weave::Window& window = Weave::Application::get().get_window();
            if (window.is_maximized()) {
                window.restore();
            }
            else {
                window.maximize();
            }
        }
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.1f, 1.0f));

        ImTextureID close_tex_id = (ImTextureID)(intptr_t)this->icon_close_id;
        if (ImGui::ImageButton("##close", close_tex_id, ImVec2(icon_size, icon_size), ImVec2(0, 1), ImVec2(1, 0))) {
            Weave::Application::get().close();
        }

        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);
        ImGui::EndMenuBar();
    }
}

void SandboxLayer::render_viewport() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.12f, 0.12f, 0.12f, 1.0f));
    const bool visible = ImGui::Begin("Viewport");

    ImVec2 viewport_panel_size = ImGui::GetContentRegionAvail();
    const auto& spec = this->framebuffer->get_specification();

    const ImVec2 scale = ImGui::GetWindowViewport()->FramebufferScale;
    const double pixel_width = std::floor(viewport_panel_size.x * scale.x);
    const double pixel_height = std::floor(viewport_panel_size.y * scale.y);
    if (visible && std::isfinite(pixel_width) && std::isfinite(pixel_height) && pixel_width >= 1 && pixel_height >= 1 &&
        pixel_width <= std::numeric_limits<int32_t>::max() && pixel_height <= std::numeric_limits<int32_t>::max()) {
        uint32_t width = static_cast<uint32_t>(pixel_width);
        uint32_t height = static_cast<uint32_t>(pixel_height);

        if (width > 0 && height > 0 && (spec.width != width || spec.height != height)) {
            this->framebuffer->resize(width, height);
            this->camera.set_viewport_size(width, height);
        }

        this->render_scene();
        ImTextureID texture_id = (ImTextureID)(intptr_t)this->framebuffer->get_color_attachment_renderer_id();
        ImGui::Image(texture_id, viewport_panel_size, ImVec2{0, 1}, ImVec2{1, 0});
    }

    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(3);
}

void SandboxLayer::render_settings() {
    ImGui::Begin("Settings");

    static constexpr const char* projection_types[] = {"Perspective", "Orthographic"};
    int current_projection = static_cast<int>(this->camera.get_projection_type());

    if (ImGui::Combo("Projection", &current_projection, projection_types, IM_ARRAYSIZE(projection_types))) {
        this->camera.set_projection_type(static_cast<Weave::Camera::ProjectionType>(current_projection));
    }

    ImGui::DragFloat3("Position", &this->camera_position.x, 0.1f);

    if (this->camera.get_projection_type() == Weave::Camera::ProjectionType::Perspective) {
        float fov = this->camera.get_perspective_vertical_fov();
        if (ImGui::SliderFloat("FOV", &fov, 1.f, 120.f)) {
            this->camera.set_perspective_vertical_fov(fov);
        }
    }
    else {
        float size = this->camera.get_orthographic_size();
        if (ImGui::DragFloat("Ortho Size", &size, 0.1f)) {
            this->camera.set_orthographic_size(size);
        }
    }

    ImGui::End();
}

void SandboxLayer::render_about_menu() {
    ImGui::SetNextWindowSize({200, 70}, ImGuiCond_FirstUseEver);
    ImGui::Begin("About Weave", &this->show_about_menu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking);

    ImGui::Text(std::format("Weave {}", WEAVE_VERSION).c_str());

    ImGui::End();
}

uint32_t SandboxLayer::load_texture_from_file(const char* path) {
    int width, height, channels;

    stbi_set_flip_vertically_on_load(1);

    unsigned char* data = stbi_load(path, &width, &height, &channels, 4);
    if (!data) {
        return 0;
    }

    uint32_t texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    return texture_id;
}
