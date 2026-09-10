#include "sandbox_layer.h"
#include <glad/glad.h>
#include <imgui.h>
// #include "weave/core/log.h"

SandboxLayer::SandboxLayer() : Layer("SandboxLayer") { }

void SandboxLayer::on_attach() {
    this->vertex_array.reset(Weave::VertexArray::create());

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    
    this->vertex_buffer.reset(Weave::VertexBuffer::create(vertices, sizeof(vertices)));

    Weave::BufferLayout layout = {
        { Weave::ShaderDataType::Float3, "aPos" },
        { Weave::ShaderDataType::Float3, "color" }
    };
    this->vertex_buffer->set_layout(layout);
    this->vertex_array->add_vertex_buffer(this->vertex_buffer);

    uint32_t indices[] = { 0, 1, 2 };
    this->index_buffer.reset(Weave::IndexBuffer::create(indices, 3));
    this->vertex_array->set_index_buffer(this->index_buffer);
    
    const char* vertex_shader_source = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 color;
        out vec3 vertexColor;
        void main() {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

void SandboxLayer::on_detach() {
    glDeleteVertexArrays(1, &VAO);
}

void SandboxLayer::on_update() {
    this->shader->bind();
    Weave::Renderer::draw_indexed(this->vertex_array);
}

void SandboxLayer::on_event(Weave::Event& event) {
    // WEAVE_LOG_INFO_TAG("Sandbox Layer", "{}", event.to_string());
}

void SandboxLayer::on_imgui_render() {
    static bool show_demo_window = true;
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    static ImVec4 color(0.f, 0.f, 0.f, 1.f);

    ImGui::Begin("Window");
    ImGui::ColorPicker4("Fav color", (float*)&color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar);
    ImGui::End();
}
