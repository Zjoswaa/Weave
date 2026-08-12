#include "weave/PCH.h"
#include "weave/core/application.h"
#include "weave/platform/opengl/opengl_imgui_layer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Weave {
    OpenGlImGuiLayer::OpenGlImGuiLayer() = default;

    void OpenGlImGuiLayer::on_attach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        io.Fonts->AddFontFromFileTTF("assets/fonts/JetBrainsMonoNL-Regular.ttf", 18.f);
        io.FontDefault = io.Fonts->Fonts.back();

        ImGui::StyleColorsDark();
        this->set_custom_dark_theme();
        this->set_custom_style();

        // ImGuiStyle& style = ImGui::GetStyle();
        // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        //     style.WindowRounding = 0.0f;
        //     style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        // }

        Application& app = Application::get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.get_window().get_native_window());
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    void OpenGlImGuiLayer::on_detach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void OpenGlImGuiLayer::begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void OpenGlImGuiLayer::end() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            // GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            // glfwMakeContextCurrent(backup_current_context);
        }
    }
}
