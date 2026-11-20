#include "sandbox_layer.h"
#include "weave/core/log.h"
#include "weave/core/version.h"

#include <glad/glad.h>
#include <imgui.h>

SandboxLayer::SandboxLayer() : Weave::Layer("SandboxLayer") { }

void SandboxLayer::on_attach() {
    float vertices[6 * 3] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f,
         0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f,
         0.0f,  0.5f, 0.0f, 0.2f, 0.2f, 0.8f
    };

    uint32_t indices[3] {
        0, 1, 2
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const char* vertex_shader_source = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 color;
            out vec3 vertexColor;
            void main() {
                gl_Position = vec4(aPos, 1.0);
                vertexColor = color;
            }
        )";
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    const char* fragment_shader_source = R"(
            #version 330 core
            out vec4 FragColor;
            in vec3 vertexColor;
            void main() {
                FragColor = vec4(vertexColor, 1.0f);
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
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteProgram(shader_program);
}

void SandboxLayer::on_update() {
    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
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
