#include "sandbox_layer.h"
#include <glad/glad.h>
#include <imgui.h>
// #include "weave/core/log.h"

SandboxLayer::SandboxLayer() : Layer("SandboxLayer") { }

void SandboxLayer::on_attach() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

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
    glDeleteProgram(shader_program);
}

void SandboxLayer::on_update() {
    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
