#include "weave/PCH.h"
#include "weave/core/events/event.h"
#include "weave/imgui/imgui_layer.h"
#include "weave/platform/opengl/opengl_imgui_layer.h"

#include "imgui.h"
#include "weave/core/log.h"

namespace Weave {
    static ImGuiKey to_imgui_key(Weave::KeyCode key_code) {
        switch (key_code) {
            case KeyCode::A: return ImGuiKey_A;
            case KeyCode::B: return ImGuiKey_B;
            case KeyCode::C: return ImGuiKey_C;
            case KeyCode::D: return ImGuiKey_D;
            case KeyCode::E: return ImGuiKey_E;
            case KeyCode::F: return ImGuiKey_F;
            case KeyCode::G: return ImGuiKey_G;
            case KeyCode::H: return ImGuiKey_H;
            case KeyCode::I: return ImGuiKey_I;
            case KeyCode::J: return ImGuiKey_J;
            case KeyCode::K: return ImGuiKey_K;
            case KeyCode::L: return ImGuiKey_L;
            case KeyCode::M: return ImGuiKey_M;
            case KeyCode::N: return ImGuiKey_N;
            case KeyCode::O: return ImGuiKey_O;
            case KeyCode::P: return ImGuiKey_P;
            case KeyCode::Q: return ImGuiKey_Q;
            case KeyCode::R: return ImGuiKey_R;
            case KeyCode::S: return ImGuiKey_S;
            case KeyCode::T: return ImGuiKey_T;
            case KeyCode::U: return ImGuiKey_U;
            case KeyCode::V: return ImGuiKey_V;
            case KeyCode::W: return ImGuiKey_W;
            case KeyCode::X: return ImGuiKey_X;
            case KeyCode::Y: return ImGuiKey_Y;
            case KeyCode::Z: return ImGuiKey_Z;

            case KeyCode::D1: return ImGuiKey_1;
            case KeyCode::D2: return ImGuiKey_2;
            case KeyCode::D3: return ImGuiKey_3;
            case KeyCode::D4: return ImGuiKey_4;
            case KeyCode::D5: return ImGuiKey_5;
            case KeyCode::D6: return ImGuiKey_6;
            case KeyCode::D7: return ImGuiKey_7;
            case KeyCode::D8: return ImGuiKey_8;
            case KeyCode::D9: return ImGuiKey_9;
            case KeyCode::D0: return ImGuiKey_0;

            case KeyCode::Return:    return ImGuiKey_Enter;
            case KeyCode::Escape:    return ImGuiKey_Escape;
            case KeyCode::Backspace: return ImGuiKey_Backspace;
            case KeyCode::Tab:       return ImGuiKey_Tab;
            case KeyCode::Space:     return ImGuiKey_Space;

            case KeyCode::Minus:        return ImGuiKey_Minus;
            case KeyCode::Equal:        return ImGuiKey_Equal;
            case KeyCode::LeftBracket:  return ImGuiKey_LeftBracket;
            case KeyCode::RightBracket: return ImGuiKey_RightBracket;
            case KeyCode::Backslash:    return ImGuiKey_Backslash;
            case KeyCode::Semicolon:    return ImGuiKey_Semicolon;
            case KeyCode::Apostrophe:   return ImGuiKey_Apostrophe;
            case KeyCode::Grave:        return ImGuiKey_GraveAccent;
            case KeyCode::Comma:        return ImGuiKey_Comma;
            case KeyCode::Period:       return ImGuiKey_Period;
            case KeyCode::Slash:        return ImGuiKey_Slash;

            case KeyCode::CapsLock:    return ImGuiKey_CapsLock;
            case KeyCode::ScrollLock:  return ImGuiKey_ScrollLock;
            case KeyCode::NumLock:     return ImGuiKey_NumLock;
            case KeyCode::PrintScreen: return ImGuiKey_PrintScreen;
            case KeyCode::Pause:       return ImGuiKey_Pause;

            case KeyCode::F1:  return ImGuiKey_F1;
            case KeyCode::F2:  return ImGuiKey_F2;
            case KeyCode::F3:  return ImGuiKey_F3;
            case KeyCode::F4:  return ImGuiKey_F4;
            case KeyCode::F5:  return ImGuiKey_F5;
            case KeyCode::F6:  return ImGuiKey_F6;
            case KeyCode::F7:  return ImGuiKey_F7;
            case KeyCode::F8:  return ImGuiKey_F8;
            case KeyCode::F9:  return ImGuiKey_F9;
            case KeyCode::F10: return ImGuiKey_F10;
            case KeyCode::F11: return ImGuiKey_F11;
            case KeyCode::F12: return ImGuiKey_F12;

            case KeyCode::PageUp:   return ImGuiKey_PageUp;
            case KeyCode::PageDown: return ImGuiKey_PageDown;
            case KeyCode::Insert:   return ImGuiKey_Insert;
            case KeyCode::Home:     return ImGuiKey_Home;
            case KeyCode::Delete:   return ImGuiKey_Delete;
            case KeyCode::End:      return ImGuiKey_End;

            case KeyCode::Left:     return ImGuiKey_LeftArrow;
            case KeyCode::Right:    return ImGuiKey_RightArrow;
            case KeyCode::Up:       return ImGuiKey_UpArrow;
            case KeyCode::Down:     return ImGuiKey_DownArrow;

            case KeyCode::KeyPadDivide:   return ImGuiKey_KeypadDivide;
            case KeyCode::KeyPadMultiply: return ImGuiKey_KeypadMultiply;
            case KeyCode::KeyPadSubtract: return ImGuiKey_KeypadSubtract;
            case KeyCode::KeyPadAdd:      return ImGuiKey_KeypadAdd;
            case KeyCode::KeyPadReturn:   return ImGuiKey_KeypadEnter;
            case KeyCode::KeyPad1:        return ImGuiKey_Keypad1;
            case KeyCode::KeyPad2:        return ImGuiKey_Keypad2;
            case KeyCode::KeyPad3:        return ImGuiKey_Keypad3;
            case KeyCode::KeyPad4:        return ImGuiKey_Keypad4;
            case KeyCode::KeyPad5:        return ImGuiKey_Keypad5;
            case KeyCode::KeyPad6:        return ImGuiKey_Keypad6;
            case KeyCode::KeyPad7:        return ImGuiKey_Keypad7;
            case KeyCode::KeyPad8:        return ImGuiKey_Keypad8;
            case KeyCode::KeyPad9:        return ImGuiKey_Keypad9;
            case KeyCode::KeyPad0:        return ImGuiKey_Keypad0;
            case KeyCode::KeyPadPeriod:   return ImGuiKey_KeypadDecimal;

            case KeyCode::LeftControl:  return ImGuiKey_LeftCtrl;
            case KeyCode::LeftShift:    return ImGuiKey_LeftShift;
            case KeyCode::LeftAlt:      return ImGuiKey_LeftAlt;
            case KeyCode::LeftSuper:    return ImGuiKey_LeftSuper;
            case KeyCode::RightControl: return ImGuiKey_RightCtrl;
            case KeyCode::RightShift:   return ImGuiKey_RightShift;
            case KeyCode::RightAlt:     return ImGuiKey_RightAlt;
            case KeyCode::RightSuper:   return ImGuiKey_RightSuper;
            case KeyCode::Menu:         return ImGuiKey_Menu;

            case KeyCode::Unknown:
            default:
                return ImGuiKey_None;
        }
    }

    ImGuiLayer* ImGuiLayer::create() {
        return new Weave::OpenGL::ImGuiLayer();
    }

    void ImGuiLayer::set_custom_dark_theme() {
        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text]                      = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]              = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg]                  = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_ChildBg]                   = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                   = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        colors[ImGuiCol_Border]                    = ImVec4(0.19f, 0.19f, 0.19f, 0.5f);
        colors[ImGuiCol_BorderShadow]              = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
        colors[ImGuiCol_FrameBg]                   = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_FrameBgHovered]            = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_FrameBgActive]             = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_TitleBg]                   = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_TitleBgActive]             = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        colors[ImGuiCol_MenuBarBg]                 = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]               = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ScrollbarGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabHovered]      = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_CheckMark]                 = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_SliderGrab]                = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_SliderGrabActive]          = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_Button]                    = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ButtonHovered]             = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_ButtonActive]              = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_Header]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_HeaderHovered]             = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
        colors[ImGuiCol_HeaderActive]              = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
        colors[ImGuiCol_Separator]                 = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_SeparatorHovered]          = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_SeparatorActive]           = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_ResizeGrip]                = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_ResizeGripHovered]         = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_ResizeGripActive]          = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_Tab]                       = ImVec4(1.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabHovered]                = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        // colors[ImGuiCol_TabActive]                 = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
        // colors[ImGuiCol_TabUnfocused]              = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        // colors[ImGuiCol_TabUnfocusedActive]        = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.21176470588235294f, 0.8705882352941177f, 0.5843137254901961f, 0.25f);
        //colors[ImGuiCol_TabSelectedOverline]       = ImVec4(0.38823529f, 0.58431372f, 0.93333333f, 1.0f);
        colors[ImGuiCol_TabSelectedOverline]       = ImVec4(0.21176470588235294f, 0.8705882352941177f, 0.5843137254901961f, 1.00f);
        colors[ImGuiCol_DockingPreview]            = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_DockingEmptyBg]            = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotLines]                 = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogram]             = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered]      = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderStrong]         = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderLight]          = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_TableRowBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt]             = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextSelectedBg]            = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_DragDropTarget]            = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_NavHighlight]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]     = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]         = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg]          = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
    }

    void ImGuiLayer::set_custom_style() {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding                     = ImVec2(8.00f, 8.00f);
        style.FramePadding                      = ImVec2(5.00f, 2.00f);
        style.CellPadding                       = ImVec2(6.00f, 6.00f);
        style.ItemSpacing                       = ImVec2(6.00f, 6.00f);
        style.ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
        style.TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
        style.IndentSpacing                     = 25;
        style.ScrollbarSize                     = 15;
        style.GrabMinSize                       = 10;
        style.WindowBorderSize                  = 0;
        style.ChildBorderSize                   = 1;
        style.PopupBorderSize                   = 1;
        style.FrameBorderSize                   = 1;
        style.TabBorderSize                     = 0;
        style.WindowRounding                    = 0;
        style.ChildRounding                     = 0;
        style.FrameRounding                     = 4;
        style.PopupRounding                     = 4;
        style.ScrollbarRounding                 = 9;
        style.GrabRounding                      = 3;
        style.LogSliderDeadzone                 = 4;
        style.TabRounding                       = 0;
        style.DockingSeparatorSize              = 1;
        style.DockingNodeHasCloseButton         = false;
        style.WindowMenuButtonPosition          = ImGuiDir_None;
    }

    void ImGuiLayer::on_event(Weave::Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<KeyPressEvent>([this](KeyPressEvent& e) {
            return this->on_key_press_event(e);
        });
        dispatcher.dispatch<KeyReleaseEvent>([this](KeyReleaseEvent& e) {
            return this->on_key_release_event(e);
        });
        dispatcher.dispatch<KeyTypeEvent>([this](KeyTypeEvent& e) {
            return this->on_key_type_event(e);
        });
        dispatcher.dispatch<MouseButtonPressEvent>([this](MouseButtonPressEvent& e) {
            return this->on_mouse_button_press_event(e);
        });
        dispatcher.dispatch<MouseButtonReleaseEvent>([this](MouseButtonReleaseEvent& e) {
            return this->on_mouse_button_release_event(e);
        });
        dispatcher.dispatch<MouseMoveEvent>([this](MouseMoveEvent& e) {
            return this->on_mouse_move_event(e);
        });
        dispatcher.dispatch<MouseScrollEvent>([this](MouseScrollEvent& e) {
            return this->on_mouse_scroll_event(e);
        });
        dispatcher.dispatch<WindowResizeEvent>([this](WindowResizeEvent& e) {
            return this->on_window_resize_event(e);
        });
    }


    bool ImGuiLayer::on_key_press_event(KeyPressEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        KeyCode key_code = e.get_key_code();

        // Update key mods
        if (key_code == KeyCode::LeftControl || key_code == KeyCode::RightControl) {
            io.AddKeyEvent(ImGuiMod_Ctrl, true);
        } else if (key_code == KeyCode::LeftShift || key_code == KeyCode::RightShift) {
            io.AddKeyEvent(ImGuiMod_Shift, true);
        } else if (key_code == KeyCode::LeftAlt || key_code == KeyCode::RightAlt) {
            io.AddKeyEvent(ImGuiMod_Alt, true);
        } else if (key_code == KeyCode::LeftSuper || key_code == KeyCode::RightSuper) {
            io.AddKeyEvent(ImGuiMod_Super, true);
        }

        const ImGuiKey imgui_key = to_imgui_key(key_code);
        if (imgui_key == ImGuiKey_None) {
            return false;
        }
        io.AddKeyEvent(imgui_key, true);
        return io.WantCaptureKeyboard;
    }

    bool ImGuiLayer::on_key_release_event(KeyReleaseEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        KeyCode key_code = e.get_key_code();

        // Update key mods
        if (key_code == KeyCode::LeftControl || key_code == KeyCode::RightControl) {
            io.AddKeyEvent(ImGuiMod_Ctrl, false);
        } else if (key_code == KeyCode::LeftShift || key_code == KeyCode::RightShift) {
            io.AddKeyEvent(ImGuiMod_Shift, false);
        } else if (key_code == KeyCode::LeftAlt || key_code == KeyCode::RightAlt) {
            io.AddKeyEvent(ImGuiMod_Alt, false);
        } else if (key_code == KeyCode::LeftSuper || key_code == KeyCode::RightSuper) {
            io.AddKeyEvent(ImGuiMod_Super, false);
        }

        const ImGuiKey imgui_key = to_imgui_key(e.get_key_code());
        if (imgui_key == ImGuiKey_None) {
            return false;
        }
        io.AddKeyEvent(imgui_key, false);
        return io.WantCaptureKeyboard;
    }

    bool ImGuiLayer::on_key_type_event(KeyTypeEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        int key_code = static_cast<int>(e.get_codepoint());
        if (key_code > 0 && key_code < 0x10000) {
            io.AddInputCharacter(key_code);
        }

        return false;
    }

    bool ImGuiLayer::on_mouse_button_press_event(MouseButtonPressEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        switch (e.get_mouse_button()) {
            case MouseButton::Left:
                io.MouseDown[ImGuiMouseButton_Left] = true;
                break;
            case MouseButton::Right:
                io.MouseDown[ImGuiMouseButton_Right] = true;
                break;
            case MouseButton::Middle:
                io.MouseDown[ImGuiMouseButton_Middle] = true;
                break;
            default:
                break;
        }

        return false;
    }

    bool ImGuiLayer::on_mouse_button_release_event(MouseButtonReleaseEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        switch (e.get_mouse_button()) {
            case MouseButton::Left:
                io.MouseDown[ImGuiMouseButton_Left] = false;
                break;
            case MouseButton::Right:
                io.MouseDown[ImGuiMouseButton_Right] = false;
                break;
            case MouseButton::Middle:
                io.MouseDown[ImGuiMouseButton_Middle] = false;
                break;
            default:
                break;
        }

        return false;
    }

    bool ImGuiLayer::on_mouse_move_event(MouseMoveEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.get_x(), e.get_y());

        return false;
    }

    bool ImGuiLayer::on_mouse_scroll_event(MouseScrollEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheel += e.get_y_offset();
        io.MouseWheelH += e.get_x_offset();

        return false;
    }

    bool ImGuiLayer::on_window_resize_event(WindowResizeEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.get_width(), e.get_height());

        return false;
    }
}
