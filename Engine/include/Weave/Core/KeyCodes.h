#ifndef WEAVE_KEYCODE_H
#define WEAVE_KEYCODE_H

#include "Weave/PCH.h"

namespace Weave {
    enum class KeyCode : uint16_t {
        A = 1,
        B = 2,
        C = 3,
        D = 4,
        E = 5,
        F = 6,
        G = 7,
        H = 8,
        I = 9,
        J = 10,
        K = 11,
        L = 12,
        M = 13,
        N = 14,
        O = 15,
        P = 16,
        Q = 17,
        R = 18,
        S = 19,
        T = 20,
        U = 21,
        V = 22,
        W = 23,
        X = 24,
        Y = 25,
        Z = 26,

        D1 = 27,
        D2 = 28,
        D3 = 29,
        D4 = 30,
        D5 = 31,
        D6 = 32,
        D7 = 33,
        D8 = 34,
        D9 = 35,
        D0 = 36,

        Return = 37,
        Escape = 38,
        Backspace = 39,
        Tab = 40,
        Space = 41,

        Minus = 42,
        Equal = 43,
        LeftBracket = 44,
        RightBracket = 45,
        Backslash = 46,
        Semicolon = 47,
        Apostrophe = 48,
        Grave = 49,
        Comma = 50,
        Period = 51,
        Slash = 52,

        CapsLock = 53,

        F1 = 54,
        F2 = 55,
        F3 = 56,
        F4 = 57,
        F5 = 58,
        F6 = 59,
        F7 = 60,
        F8 = 61,
        F9 = 62,
        F10 = 63,
        F11 = 64,
        F12 = 65,

        Home = 66,
        PageUp = 67,
        Delete = 68,
        End = 69,
        PageDown = 70,
        Right = 71,
        Left = 72,
        Down = 73,
        Up = 74,
        NumLock = 75,

        KeyPadDivide = 76,
        KeyPadMultiply = 77,
        KeyPadMinus = 78,
        KeyPadPlus = 79,
        KeyPadReturn = 80,
        KeyPad1 = 81,
        KeyPad2 = 82,
        KeyPad3 = 83,
        KeyPad4 = 84,
        KeyPad5 = 85,
        KeyPad6 = 86,
        KeyPad7 = 87,
        KeyPad8 = 88,
        KeyPad9 = 89,
        KeyPad0 = 90,
        KeyPadPeriod = 91,

        LeftControl = 92,
        LeftShift = 93,
        LeftAlt = 94,
        LeftSuper = 95,
        RightControl = 96,
        RightShift = 97,
        RightAlt = 98,
        RightSuper = 99,
    };

    enum class MouseButton : uint16_t {
        Left = 1,
        Middle = 2,
        Right = 3,
        Button4 = 4,
        Button5 = 5
    };

    inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode) {
        os << static_cast<int32_t>(keyCode);
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, MouseButton mouseButton) {
        os << static_cast<int32_t>(mouseButton);
        return os;
    }
}

#define WV_KEY_A Weave::KeyCode::A
#define WV_KEY_B Weave::KeyCode::B
#define WV_KEY_C Weave::KeyCode::C
#define WV_KEY_D Weave::KeyCode::D
#define WV_KEY_E Weave::KeyCode::E
#define WV_KEY_F Weave::KeyCode::F
#define WV_KEY_G Weave::KeyCode::G
#define WV_KEY_H Weave::KeyCode::H
#define WV_KEY_I Weave::KeyCode::I
#define WV_KEY_J Weave::KeyCode::J
#define WV_KEY_K Weave::KeyCode::K
#define WV_KEY_L Weave::KeyCode::L
#define WV_KEY_M Weave::KeyCode::M
#define WV_KEY_N Weave::KeyCode::N
#define WV_KEY_O Weave::KeyCode::O
#define WV_KEY_P Weave::KeyCode::P
#define WV_KEY_Q Weave::KeyCode::Q
#define WV_KEY_R Weave::KeyCode::R
#define WV_KEY_S Weave::KeyCode::S
#define WV_KEY_T Weave::KeyCode::T
#define WV_KEY_U Weave::KeyCode::U
#define WV_KEY_V Weave::KeyCode::V
#define WV_KEY_W Weave::KeyCode::W
#define WV_KEY_X Weave::KeyCode::X
#define WV_KEY_Y Weave::KeyCode::Y
#define WV_KEY_Z Weave::KeyCode::Z

#define WV_KEY_1 Weave::KeyCode::D1
#define WV_KEY_2 Weave::KeyCode::D2
#define WV_KEY_3 Weave::KeyCode::D3
#define WV_KEY_4 Weave::KeyCode::D4
#define WV_KEY_5 Weave::KeyCode::D5
#define WV_KEY_6 Weave::KeyCode::D6
#define WV_KEY_7 Weave::KeyCode::D7
#define WV_KEY_8 Weave::KeyCode::D8
#define WV_KEY_9 Weave::KeyCode::D9
#define WV_KEY_0 Weave::KeyCode::D0

#define WV_KEY_RETURN Weave::KeyCode::Return
#define WV_KEY_ESCAPE Weave::KeyCode::Escape
#define WV_KEY_BACKSPACE Weave::KeyCode::Backspace
#define WV_KEY_TAB Weave::KeyCode::Tab
#define WV_KEY_SPACE Weave::KeyCode::Space

#define WV_KEY_MINUS Weave::KeyCode::Minus
#define WV_KEY_EQUAL Weave::KeyCode::Equal
#define WV_KEY_LEFT_BRACKET Weave::KeyCode::LeftBracket
#define WV_KEY_RIGHT_BRACKET Weave::KeyCode::RightBracket
#define WV_KEY_BACKSLASH Weave::KeyCode::Backslash
#define WV_KEY_SEMICOLON Weave::KeyCode::Semicolon
#define WV_KEY_APOSTROPHE Weave::KeyCode::Apostrophe
#define WV_KEY_GRAVE Weave::KeyCode::Grave
#define WV_KEY_COMMA Weave::KeyCode::Comma
#define WV_KEY_PERIOD Weave::KeyCode::Period
#define WV_KEY_SLASH Weave::KeyCode::Slash

#define WV_KEY_CAPS_LOCK Crescent::KeyCode::CapsLock

#define WV_KEY_F1 Weave::KeyCode::F1
#define WV_KEY_F2 Weave::KeyCode::F2
#define WV_KEY_F3 Weave::KeyCode::F3
#define WV_KEY_F4 Weave::KeyCode::F4
#define WV_KEY_F5 Weave::KeyCode::F5
#define WV_KEY_F6 Weave::KeyCode::F6
#define WV_KEY_F7 Weave::KeyCode::F7
#define WV_KEY_F8 Weave::KeyCode::F8
#define WV_KEY_F9 Weave::KeyCode::F9
#define WV_KEY_F10 Weave::KeyCode::F10
#define WV_KEY_F11 Weave::KeyCode::F11
#define WV_KEY_F12 Weave::KeyCode::F12

#define WV_KEY_HOME Weave::KeyCode::Home
#define WV_KEY_PAGE_UP Weave::KeyCode::PageUp
#define WV_KEY_DELETE Weave::KeyCode::Delete
#define WV_KEY_END Weave::KeyCode::End
#define WV_KEY_PAGE_DOWN Weave::KeyCode::PageDown
#define WV_KEY_RIGHT Weave::KeyCode::Right
#define WV_KEY_LEFT Weave::KeyCode::Left
#define WV_KEY_DOWN Weave::KeyCode::Down
#define WV_KEY_UP Weave::KeyCode::Up
#define WV_KEY_NUM_LOCK Weave::KeyCode::NumLock

#define WV_KEY_KP_DIVIDE Weave::KeyCode::KeyPadDivide
#define WV_KEY_KP_MULTIPLY Weave::KeyCode::KeyPadMultiply
#define WV_KEY_KP_MINUS Weave::KeyCode::KeyPadMinus
#define WV_KEY_KP_PLUS Weave::KeyCode::KeyPadPlus
#define WV_KEY_KP_RETURN Weave::KeyCode::KeyPadReturn
#define WV_KEY_KP_1 Weave::KeyCode::KeyPad1
#define WV_KEY_KP_2 Weave::KeyCode::KeyPad2
#define WV_KEY_KP_3 Weave::KeyCode::KeyPad3
#define WV_KEY_KP_4 Weave::KeyCode::KeyPad4
#define WV_KEY_KP_5 Weave::KeyCode::KeyPad5
#define WV_KEY_KP_6 Weave::KeyCode::KeyPad6
#define WV_KEY_KP_7 Weave::KeyCode::KeyPad7
#define WV_KEY_KP_8 Weave::KeyCode::KeyPad8
#define WV_KEY_KP_9 Weave::KeyCode::KeyPad9
#define WV_KEY_KP_0 Weave::KeyCode::KeyPad0
#define WV_KEY_KP_PERIOD Weave::KeyCode::KeyPadPeriod

#define WV_KEY_LEFT_CONTROL Weave::KeyCode::LeftControl
#define WV_KEY_LEFT_SHIFT Weave::KeyCode::LeftShift
#define WV_KEY_LEFT_ALT Weave::KeyCode::LeftAlt /* Alt, Option */
#define WV_KEY_LEFT_SUPER Weave::KeyCode::LeftSuper /* Windows, Command, Meta */
#define WV_KEY_RIGHT_CONTROL Weave::KeyCode::RightControl
#define WV_KEY_RIGHT_SHIFT Weave::KeyCode::RightShift
#define WV_KEY_RIGHT_ALT Weave::KeyCode::RightAlt /* Alt, Option */
#define WV_KEY_RIGHT_SUPER Weave::KeyCode::RightSuper /* Windows, Command, Meta */

#define WV_MOUSE_BUTTON_LEFT Weave::MouseButton::Left
#define WV_MOUSE_BUTTON_MIDDLE Weave::MouseButton::Middle
#define WV_MOUSE_BUTTON_RIGHT Weave::MouseButton::Right
#define WV_MOUSE_BUTTON_4 Weave::MouseButton::Button4
#define WV_MOUSE_BUTTON_5 Weave::MouseButton::Button5

#endif
