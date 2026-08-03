#include "weave/PCH.h"
#include "weave/platform/glfw/glfw_window.h"
#include "weave/core/key_codes.h"
#include "weave/core/log.h"
#include "weave/core/events/window_resize_event.h"
#include "weave/core/events/window_close_event.h"
#include "weave/core/events/key_press_event.h"
#include "weave/core/events/key_release_event.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Weave {
    static bool glfw_initialized = false;
    static std::array<Weave::KeyCode, GLFW_KEY_LAST + 1> key_lookup_table;
    static bool key_lookup_table_initialized = false;

    static void glfw_error_callback(int error, const char* description) {
        WEAVE_LOG_CORE_ERROR_TAG("GLFW", "Error ({}): {}", error, description);
    }

    static void init_key_lookup_table() {
        if (key_lookup_table_initialized) {
            return;
        }

        key_lookup_table.fill(Weave::KeyCode::Unknown);

        key_lookup_table[GLFW_KEY_A] = Weave::KeyCode::A;
        key_lookup_table[GLFW_KEY_B] = Weave::KeyCode::B;
        key_lookup_table[GLFW_KEY_C] = Weave::KeyCode::C;
        key_lookup_table[GLFW_KEY_D] = Weave::KeyCode::D;
        key_lookup_table[GLFW_KEY_E] = Weave::KeyCode::E;
        key_lookup_table[GLFW_KEY_F] = Weave::KeyCode::F;
        key_lookup_table[GLFW_KEY_G] = Weave::KeyCode::G;
        key_lookup_table[GLFW_KEY_H] = Weave::KeyCode::H;
        key_lookup_table[GLFW_KEY_I] = Weave::KeyCode::I;
        key_lookup_table[GLFW_KEY_J] = Weave::KeyCode::J;
        key_lookup_table[GLFW_KEY_K] = Weave::KeyCode::K;
        key_lookup_table[GLFW_KEY_L] = Weave::KeyCode::L;
        key_lookup_table[GLFW_KEY_M] = Weave::KeyCode::M;
        key_lookup_table[GLFW_KEY_N] = Weave::KeyCode::N;
        key_lookup_table[GLFW_KEY_O] = Weave::KeyCode::O;
        key_lookup_table[GLFW_KEY_P] = Weave::KeyCode::P;
        key_lookup_table[GLFW_KEY_Q] = Weave::KeyCode::Q;
        key_lookup_table[GLFW_KEY_R] = Weave::KeyCode::R;
        key_lookup_table[GLFW_KEY_S] = Weave::KeyCode::S;
        key_lookup_table[GLFW_KEY_T] = Weave::KeyCode::T;
        key_lookup_table[GLFW_KEY_U] = Weave::KeyCode::U;
        key_lookup_table[GLFW_KEY_V] = Weave::KeyCode::V;
        key_lookup_table[GLFW_KEY_W] = Weave::KeyCode::W;
        key_lookup_table[GLFW_KEY_X] = Weave::KeyCode::X;
        key_lookup_table[GLFW_KEY_Y] = Weave::KeyCode::Y;
        key_lookup_table[GLFW_KEY_Z] = Weave::KeyCode::Z;
        key_lookup_table[GLFW_KEY_1] = Weave::KeyCode::D1;
        key_lookup_table[GLFW_KEY_2] = Weave::KeyCode::D2;
        key_lookup_table[GLFW_KEY_3] = Weave::KeyCode::D3;
        key_lookup_table[GLFW_KEY_4] = Weave::KeyCode::D4;
        key_lookup_table[GLFW_KEY_5] = Weave::KeyCode::D5;
        key_lookup_table[GLFW_KEY_6] = Weave::KeyCode::D6;
        key_lookup_table[GLFW_KEY_7] = Weave::KeyCode::D7;
        key_lookup_table[GLFW_KEY_8] = Weave::KeyCode::D8;
        key_lookup_table[GLFW_KEY_9] = Weave::KeyCode::D9;
        key_lookup_table[GLFW_KEY_0] = Weave::KeyCode::D0;
        key_lookup_table[GLFW_KEY_ENTER] = Weave::KeyCode::Return;
        key_lookup_table[GLFW_KEY_ESCAPE] = Weave::KeyCode::Escape;
        key_lookup_table[GLFW_KEY_BACKSPACE] = Weave::KeyCode::Backspace;
        key_lookup_table[GLFW_KEY_TAB] = Weave::KeyCode::Tab;
        key_lookup_table[GLFW_KEY_SPACE] = Weave::KeyCode::Space;
        key_lookup_table[GLFW_KEY_MINUS] = Weave::KeyCode::Minus;
        key_lookup_table[GLFW_KEY_EQUAL] = Weave::KeyCode::Equal;
        key_lookup_table[GLFW_KEY_LEFT_BRACKET] = Weave::KeyCode::LeftBracket;
        key_lookup_table[GLFW_KEY_RIGHT_BRACKET] = Weave::KeyCode::RightBracket;
        key_lookup_table[GLFW_KEY_BACKSLASH] = Weave::KeyCode::Backslash;
        key_lookup_table[GLFW_KEY_SEMICOLON] = Weave::KeyCode::Semicolon;
        key_lookup_table[GLFW_KEY_APOSTROPHE] = Weave::KeyCode::Apostrophe;
        key_lookup_table[GLFW_KEY_GRAVE_ACCENT] = Weave::KeyCode::Grave;
        key_lookup_table[GLFW_KEY_COMMA] = Weave::KeyCode::Comma;
        key_lookup_table[GLFW_KEY_PERIOD] = Weave::KeyCode::Period;
        key_lookup_table[GLFW_KEY_SLASH] = Weave::KeyCode::Slash;
        key_lookup_table[GLFW_KEY_CAPS_LOCK] = Weave::KeyCode::CapsLock;
        key_lookup_table[GLFW_KEY_SCROLL_LOCK] = Weave::KeyCode::ScrollLock;
        key_lookup_table[GLFW_KEY_NUM_LOCK] = Weave::KeyCode::NumLock;
        key_lookup_table[GLFW_KEY_PRINT_SCREEN] = Weave::KeyCode::PrintScreen;
        key_lookup_table[GLFW_KEY_PAUSE] = Weave::KeyCode::Pause;
        key_lookup_table[GLFW_KEY_F1] = Weave::KeyCode::F1;
        key_lookup_table[GLFW_KEY_F2] = Weave::KeyCode::F2;
        key_lookup_table[GLFW_KEY_F3] = Weave::KeyCode::F3;
        key_lookup_table[GLFW_KEY_F4] = Weave::KeyCode::F4;
        key_lookup_table[GLFW_KEY_F5] = Weave::KeyCode::F5;
        key_lookup_table[GLFW_KEY_F6] = Weave::KeyCode::F6;
        key_lookup_table[GLFW_KEY_F7] = Weave::KeyCode::F7;
        key_lookup_table[GLFW_KEY_F8] = Weave::KeyCode::F8;
        key_lookup_table[GLFW_KEY_F9] = Weave::KeyCode::F9;
        key_lookup_table[GLFW_KEY_F10] = Weave::KeyCode::F10;
        key_lookup_table[GLFW_KEY_F11] = Weave::KeyCode::F11;
        key_lookup_table[GLFW_KEY_F12] = Weave::KeyCode::F12;
        key_lookup_table[GLFW_KEY_PAGE_UP] = Weave::KeyCode::PageUp;
        key_lookup_table[GLFW_KEY_PAGE_DOWN] = Weave::KeyCode::PageDown;
        key_lookup_table[GLFW_KEY_INSERT] = Weave::KeyCode::Insert;
        key_lookup_table[GLFW_KEY_HOME] = Weave::KeyCode::Home;
        key_lookup_table[GLFW_KEY_DELETE] = Weave::KeyCode::Delete;
        key_lookup_table[GLFW_KEY_END] = Weave::KeyCode::End;
        key_lookup_table[GLFW_KEY_LEFT] = Weave::KeyCode::Left;
        key_lookup_table[GLFW_KEY_RIGHT] = Weave::KeyCode::Right;
        key_lookup_table[GLFW_KEY_UP] = Weave::KeyCode::Up;
        key_lookup_table[GLFW_KEY_DOWN] = Weave::KeyCode::Down;
        key_lookup_table[GLFW_KEY_KP_DIVIDE] = Weave::KeyCode::KeyPadDivide;
        key_lookup_table[GLFW_KEY_KP_MULTIPLY] = Weave::KeyCode::KeyPadMultiply;
        key_lookup_table[GLFW_KEY_KP_SUBTRACT] = Weave::KeyCode::KeyPadSubtract;
        key_lookup_table[GLFW_KEY_KP_ADD] = Weave::KeyCode::KeyPadAdd;
        key_lookup_table[GLFW_KEY_KP_ENTER] = Weave::KeyCode::KeyPadReturn;
        key_lookup_table[GLFW_KEY_KP_1] = Weave::KeyCode::KeyPad1;
        key_lookup_table[GLFW_KEY_KP_2] = Weave::KeyCode::KeyPad2;
        key_lookup_table[GLFW_KEY_KP_3] = Weave::KeyCode::KeyPad3;
        key_lookup_table[GLFW_KEY_KP_4] = Weave::KeyCode::KeyPad4;
        key_lookup_table[GLFW_KEY_KP_5] = Weave::KeyCode::KeyPad5;
        key_lookup_table[GLFW_KEY_KP_6] = Weave::KeyCode::KeyPad6;
        key_lookup_table[GLFW_KEY_KP_7] = Weave::KeyCode::KeyPad7;
        key_lookup_table[GLFW_KEY_KP_8] = Weave::KeyCode::KeyPad8;
        key_lookup_table[GLFW_KEY_KP_9] = Weave::KeyCode::KeyPad9;
        key_lookup_table[GLFW_KEY_KP_0] = Weave::KeyCode::KeyPad0;
        key_lookup_table[GLFW_KEY_KP_DECIMAL] = Weave::KeyCode::KeyPadPeriod;
        key_lookup_table[GLFW_KEY_LEFT_CONTROL] = Weave::KeyCode::LeftControl;
        key_lookup_table[GLFW_KEY_LEFT_SHIFT] = Weave::KeyCode::LeftShift;
        key_lookup_table[GLFW_KEY_LEFT_ALT] = Weave::KeyCode::LeftAlt;
        key_lookup_table[GLFW_KEY_LEFT_SUPER] = Weave::KeyCode::LeftSuper;
        key_lookup_table[GLFW_KEY_RIGHT_CONTROL] = Weave::KeyCode::RightControl;
        key_lookup_table[GLFW_KEY_RIGHT_SHIFT] = Weave::KeyCode::RightShift;
        key_lookup_table[GLFW_KEY_RIGHT_ALT] = Weave::KeyCode::RightAlt;
        key_lookup_table[GLFW_KEY_RIGHT_SUPER] = Weave::KeyCode::RightSuper;
        key_lookup_table[GLFW_KEY_MENU] = Weave::KeyCode::Menu;

        key_lookup_table_initialized = true;
    }

    GlfwWindow::GlfwWindow(const WindowSpecification& spec) {
        this->spec = spec;
    }

    GlfwWindow::~GlfwWindow() {
        this->shutdown();
    }

    void GlfwWindow::process_events() {
        glfwPollEvents();
    }

    void GlfwWindow::swap_buffers() {
        glfwSwapBuffers(this->window);
    }

    void GlfwWindow::init() {
        this->window_data.title = this->spec.title;
        this->window_data.width = this->spec.width;
        this->window_data.height = this->spec.height;
        // this->window_data.vsync = spec.vsync;

        WEAVE_LOG_CORE_INFO("Creating window '{}' ({}x{})", this->spec.title, this->spec.width, this->spec.height);

        if (!glfw_initialized) {
            glfwSetErrorCallback(glfw_error_callback);

            int success = glfwInit();
            if (success != GLFW_TRUE) {
                WEAVE_LOG_CORE_ERROR_TAG("GLFW", "Failed to initialize");
                glfwTerminate();
                return;
            }

            glfw_initialized = true;
        }

        if (!key_lookup_table_initialized) {
            init_key_lookup_table();
            key_lookup_table_initialized = true;
        }

        // TODO: Add rendering API selection (OpenGL, Vulkan, etc.) and set the appropriate window hints based on the selected API.
        // For example, if using Vulkan, you would set the GLFW_CLIENT_API hint to GLFW_NO_API:
        // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

        if (this->spec.fullscreen) {
            GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
            if (!primary_monitor) {
                WEAVE_LOG_CORE_ERROR_TAG("GLFW", "Failed to get primary monitor for fullscreen mode");
                return;
            }
            const GLFWvidmode* mode = glfwGetVideoMode(primary_monitor);
            if (!mode) {
                WEAVE_LOG_CORE_ERROR_TAG("GLFW", "Failed to get video mode for primary monitor");
                return;
            }

            glfwWindowHint(GLFW_RED_BITS, mode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

            this->window = glfwCreateWindow(mode->width, mode->height, this->window_data.title.c_str(), primary_monitor, nullptr);
        } else {
            this->window = glfwCreateWindow((int)this->spec.width, this->spec.height, this->window_data.title.c_str(), nullptr, nullptr);
        }

        if (!this->window) {
            WEAVE_LOG_CORE_ERROR_TAG("GLFW", "Failed to create window");
            return;
        }

        glfwMakeContextCurrent(this->window);

        glfwSetWindowUserPointer(this->window, &this->window_data);

        if (glfwRawMouseMotionSupported()) {
            glfwSetInputMode(this->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        } else {
            WEAVE_LOG_CORE_WARN_TAG("Platform", "Raw mouse motion not supported");
        }

        // -- GLFW Callbacks --
        glfwSetWindowSizeCallback(this->window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            Weave::WindowResizeEvent event((uint32_t)width, (uint32_t)height);
            data.event_callback(event);
            data.width = width;
            data.height = height;
        });

        glfwSetWindowCloseCallback(this->window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            Weave::WindowCloseEvent event;
            data.event_callback(event);
        });

        glfwSetKeyCallback(this->window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            if (key < 0 || key > GLFW_KEY_LAST) {
                WEAVE_LOG_CORE_WARN_TAG("GLFW", "Key code {} is out of range (0-{})", key, GLFW_KEY_LAST);
                return;
            }

            Weave::KeyCode keycode = key_lookup_table[key];

            if (keycode == Weave::KeyCode::Unknown) {
                WEAVE_LOG_CORE_WARN_TAG("GLFW", "Unknown keycode {}", key);
                return;
            }

            switch (action) {
                case GLFW_PRESS: {
                    data.key_repeat_counts[key] = 0;

                    Weave::KeyPressEvent event(keycode, 0);
                    data.event_callback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    data.key_repeat_counts[key] = 0;

                    Weave::KeyReleaseEvent event(keycode);
                    data.event_callback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    data.key_repeat_counts[key]++;

                    Weave::KeyPressEvent event(keycode, data.key_repeat_counts[key]);
                    data.event_callback(event);
                    break;
                }
            }
        });
    }

    void GlfwWindow::shutdown() {
        glfwDestroyWindow(this->window);
        if (glfw_initialized) {
            glfwTerminate();
            glfw_initialized = false;
        }
    }
}
