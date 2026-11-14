#include "weave/PCH.h"
#include "weave/core/application.h"
#include "weave/platform/opengl/opengl_imgui_layer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Weave::OpenGL {
    ImGuiLayer::ImGuiLayer() = default;

    void ImGuiLayer::on_attach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        io.Fonts->AddFontFromFileTTF((std::filesystem::path(ASSETS_DIR) / "fonts" / "JetBrainsMonoNL-Regular.ttf").string().c_str(), 18.f);
        io.FontDefault = io.Fonts->Fonts.back();

        ImGui::StyleColorsDark();
        this->set_custom_dark_theme();
        this->set_custom_style();

        // ImGuiStyle& style = ImGui::GetStyle();
        // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        //     style.WindowRounding = 0.0f;
        //     style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        // }

#ifdef WEAVE_WINDOWING_BACKEND_GLFW
        Application& app = Application::get();
        auto* window = static_cast<GLFWwindow*>(app.get_window().get_native_window());
        ImGui_ImplGlfw_InitForOpenGL(window, true);
#endif
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    void ImGuiLayer::on_detach() {
        ImGui_ImplOpenGL3_Shutdown();
#ifdef WEAVE_WINDOWING_BACKEND_GLFW
        ImGui_ImplGlfw_Shutdown();
#endif
        ImGui::DestroyContext();
    }

    void ImGuiLayer::begin() {
        ImGui_ImplOpenGL3_NewFrame();
#ifdef WEAVE_WINDOWING_BACKEND_GLFW
        ImGui_ImplGlfw_NewFrame();
#endif
        ImGui::NewFrame();
    }

    void ImGuiLayer::end() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
#ifdef WEAVE_WINDOWING_BACKEND_GLFW
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
#endif
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
#ifdef WEAVE_WINDOWING_BACKEND_GLFW
            glfwMakeContextCurrent(backup_current_context);
#endif
        }
    }
}
