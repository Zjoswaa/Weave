#include "sandbox_layer.h"
#include "weave/core/log.h"
#include "weave/core/version.h"
#include "weave/renderer/buffer_layout.h"
#include "weave/renderer/vertex_buffer.h"

#include <glad/glad.h>
#include <imgui.h>

SandboxLayer::SandboxLayer() : Weave::Layer("SandboxLayer") { }

void SandboxLayer::on_attach() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    float vertices[7 * 3] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.f,
         0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.f,
         0.0f,  0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.f
    };
    this->vertex_buffer.reset(Weave::VertexBuffer::create(vertices, sizeof(vertices)));

    {
        Weave::BufferLayout layout = {
            { Weave::ShaderDataType::Float3, "aPos" },
            { Weave::ShaderDataType::Float4, "aColor" }
        };

        this->vertex_buffer->set_layout(layout);
    }

    uint32_t index = 0;
    const Weave::BufferLayout& layout = this->vertex_buffer->get_layout();
    for (const Weave::BufferElement& element : layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, static_cast<GLint>(element.get_component_count()), element.get_opengl_type(), element.normalized ? GL_TRUE : GL_FALSE, static_cast<GLsizei>(layout.get_stride()), (const void*)element.offset);
        index++;
    }

    uint32_t indices[3] {
        0, 1, 2
    };
    this->index_buffer.reset(Weave::IndexBuffer::create(indices, 3));

    const char* vertex_shader_source = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec4 aColor;
            out vec4 vertexColor;
            void main() {
                gl_Position = vec4(aPos, 1.0);
                vertexColor = aColor;
            }
        )";
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    const char* fragment_shader_source = R"(
            #version 330 core
            out vec4 FragColor;
            in vec4 vertexColor;
            void main() {
                FragColor = vertexColor;
            }
        )";
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void SandboxLayer::on_detach() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shader_program);
}

void SandboxLayer::on_update() {
    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->index_buffer->get_count()), GL_UNSIGNED_INT, nullptr);
}

void SandboxLayer::on_event(Weave::Event& event) {
    // WEAVE_LOG_INFO_TAG("Sandbox Layer", "{}", event.to_string());
}

void SandboxLayer::on_imgui_render() {
    static bool show_demo_window = true;
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    ImGui::Begin("Renderer", nullptr, ImGuiWindowFlags_NoResize);
    ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
    ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
    ImGui::Text("Version: %s", glGetString(GL_VERSION));
    ImGui::End();

    ImGui::Begin("Weave", nullptr, ImGuiWindowFlags_NoResize);
    ImGui::Text("Version: %s", WEAVE_VERSION);
    ImGui::End();
}
