#pragma once

#include "ui.hpp"
#include <functional>
#include <array>
#include "config.h"

#define CUSTOM_ID 1000

enum class KeyboardAndMouse
{
    KEY_NULL = 0, // Key: NULL, used for no key pressed
    // Alphanumeric keys
    KEY_APOSTROPHE = 39,    // Key: '
    KEY_COMMA = 44,         // Key: ,
    KEY_MINUS = 45,         // Key: -
    KEY_PERIOD = 46,        // Key: .
    KEY_SLASH = 47,         // Key: /
    KEY_ZERO = 48,          // Key: 0
    KEY_ONE = 49,           // Key: 1
    KEY_TWO = 50,           // Key: 2
    KEY_THREE = 51,         // Key: 3
    KEY_FOUR = 52,          // Key: 4
    KEY_FIVE = 53,          // Key: 5
    KEY_SIX = 54,           // Key: 6
    KEY_SEVEN = 55,         // Key: 7
    KEY_EIGHT = 56,         // Key: 8
    KEY_NINE = 57,          // Key: 9
    KEY_SEMICOLON = 59,     // Key: ;
    KEY_EQUAL = 61,         // Key: =
    KEY_A = 65,             // Key: A | a
    KEY_B = 66,             // Key: B | b
    KEY_C = 67,             // Key: C | c
    KEY_D = 68,             // Key: D | d
    KEY_E = 69,             // Key: E | e
    KEY_F = 70,             // Key: F | f
    KEY_G = 71,             // Key: G | g
    KEY_H = 72,             // Key: H | h
    KEY_I = 73,             // Key: I | i
    KEY_J = 74,             // Key: J | j
    KEY_K = 75,             // Key: K | k
    KEY_L = 76,             // Key: L | l
    KEY_M = 77,             // Key: M | m
    KEY_N = 78,             // Key: N | n
    KEY_O = 79,             // Key: O | o
    KEY_P = 80,             // Key: P | p
    KEY_Q = 81,             // Key: Q | q
    KEY_R = 82,             // Key: R | r
    KEY_S = 83,             // Key: S | s
    KEY_T = 84,             // Key: T | t
    KEY_U = 85,             // Key: U | u
    KEY_V = 86,             // Key: V | v
    KEY_W = 87,             // Key: W | w
    KEY_X = 88,             // Key: X | x
    KEY_Y = 89,             // Key: Y | y
    KEY_Z = 90,             // Key: Z | z
    KEY_LEFT_BRACKET = 91,  // Key: [
    KEY_BACKSLASH = 92,     // Key: '\'
    KEY_RIGHT_BRACKET = 93, // Key: ]
    KEY_GRAVE = 96,         // Key: `
    // Function keys
    KEY_SPACE = 32,          // Key: Space
    KEY_ESCAPE = 256,        // Key: Esc
    KEY_ENTER = 257,         // Key: Enter
    KEY_TAB = 258,           // Key: Tab
    KEY_BACKSPACE = 259,     // Key: Backspace
    KEY_INSERT = 260,        // Key: Ins
    KEY_DELETE = 261,        // Key: Del
    KEY_RIGHT = 262,         // Key: Cursor right
    KEY_LEFT = 263,          // Key: Cursor left
    KEY_DOWN = 264,          // Key: Cursor down
    KEY_UP = 265,            // Key: Cursor up
    KEY_PAGE_UP = 266,       // Key: Page up
    KEY_PAGE_DOWN = 267,     // Key: Page down
    KEY_HOME = 268,          // Key: Home
    KEY_END = 269,           // Key: End
    KEY_CAPS_LOCK = 280,     // Key: Caps lock
    KEY_SCROLL_LOCK = 281,   // Key: Scroll down
    KEY_NUM_LOCK = 282,      // Key: Num lock
    KEY_PRINT_SCREEN = 283,  // Key: Print screen
    KEY_PAUSE = 284,         // Key: Pause
    KEY_F1 = 290,            // Key: F1
    KEY_F2 = 291,            // Key: F2
    KEY_F3 = 292,            // Key: F3
    KEY_F4 = 293,            // Key: F4
    KEY_F5 = 294,            // Key: F5
    KEY_F6 = 295,            // Key: F6
    KEY_F7 = 296,            // Key: F7
    KEY_F8 = 297,            // Key: F8
    KEY_F9 = 298,            // Key: F9
    KEY_F10 = 299,           // Key: F10
    KEY_F11 = 300,           // Key: F11
    KEY_F12 = 301,           // Key: F12
    KEY_LEFT_SHIFT = 340,    // Key: Shift left
    KEY_LEFT_CONTROL = 341,  // Key: Control left
    KEY_LEFT_ALT = 342,      // Key: Alt left
    KEY_LEFT_SUPER = 343,    // Key: Super left
    KEY_RIGHT_SHIFT = 344,   // Key: Shift right
    KEY_RIGHT_CONTROL = 345, // Key: Control right
    KEY_RIGHT_ALT = 346,     // Key: Alt right
    KEY_RIGHT_SUPER = 347,   // Key: Super right
    KEY_KB_MENU = 348,       // Key: KB menu
    // Keypad keys
    KEY_KP_0 = 320,        // Key: Keypad 0
    KEY_KP_1 = 321,        // Key: Keypad 1
    KEY_KP_2 = 322,        // Key: Keypad 2
    KEY_KP_3 = 323,        // Key: Keypad 3
    KEY_KP_4 = 324,        // Key: Keypad 4
    KEY_KP_5 = 325,        // Key: Keypad 5
    KEY_KP_6 = 326,        // Key: Keypad 6
    KEY_KP_7 = 327,        // Key: Keypad 7
    KEY_KP_8 = 328,        // Key: Keypad 8
    KEY_KP_9 = 329,        // Key: Keypad 9
    KEY_KP_DECIMAL = 330,  // Key: Keypad .
    KEY_KP_DIVIDE = 331,   // Key: Keypad /
    KEY_KP_MULTIPLY = 332, // Key: Keypad *
    KEY_KP_SUBTRACT = 333, // Key: Keypad -
    KEY_KP_ADD = 334,      // Key: Keypad +
    KEY_KP_ENTER = 335,    // Key: Keypad Enter
    KEY_KP_EQUAL = 336,    // Key: Keypad =
    // Android key buttons
    KEY_BACK = 4,         // Key: Android back button
    KEY_MENU = 5,         // Key: Android menu button
    KEY_VOLUME_UP = 24,   // Key: Android volume up button
    KEY_VOLUME_DOWN = 25, // Key: Android volume down button

    // Mouse buttons and cursor
    MOUSE_BUTTON_LEFT = CUSTOM_ID + 0,    // Mouse button left
    MOUSE_BUTTON_RIGHT = CUSTOM_ID + 1,   // Mouse button right
    MOUSE_BUTTON_MIDDLE = CUSTOM_ID + 2,  // Mouse button middle (pressed wheel)
    MOUSE_BUTTON_SIDE = CUSTOM_ID + 3,    // Mouse button side (advanced mouse device)
    MOUSE_BUTTON_EXTRA = CUSTOM_ID + 4,   // Mouse button extra (advanced mouse device)
    MOUSE_BUTTON_FORWARD = CUSTOM_ID + 5, // Mouse button forward (advanced mouse device)
    MOUSE_BUTTON_BACK = CUSTOM_ID + 6,    // Mouse button back (advanced mouse device)
    MOUSE_WHEEL_UP = CUSTOM_ID + 7,       // Mouse wheel up (volume up)
    MOUSE_WHEEL_DOWN = CUSTOM_ID + 8,     // Mouse wheel down (volume down)
    MOUSE_WHEEL_LEFT = CUSTOM_ID + 9,     // Mouse wheel left (scroll left)
    MOUSE_WHEEL_RIGHT = CUSTOM_ID + 10,   // Mouse wheel right (scroll right)
    MOUSE_CURSOR_UP = CUSTOM_ID + 11,     // Mouse cursor up (scroll up)
    MOUSE_CURSOR_DOWN = CUSTOM_ID + 12,   // Mouse cursor down (scroll down)
    MOUSE_CURSOR_LEFT = CUSTOM_ID + 13,   // Mouse cursor left (scroll left)
    MOUSE_CURSOR_RIGHT = CUSTOM_ID + 14,  // Mouse cursor right (scroll right)
};

enum class GamePad
{
    UNKNOWN = 0,      // Unknown button, just for error checking
    LEFT_FACE_UP,     // Gamepad left DPAD up button
    LEFT_FACE_RIGHT,  // Gamepad left DPAD right button
    LEFT_FACE_DOWN,   // Gamepad left DPAD down button
    LEFT_FACE_LEFT,   // Gamepad left DPAD left button
    RIGHT_FACE_UP,    // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
    RIGHT_FACE_RIGHT, // Gamepad right button right (i.e. PS3: Circle, Xbox: B)
    RIGHT_FACE_DOWN,  // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
    RIGHT_FACE_LEFT,  // Gamepad right button left (i.e. PS3: Square, Xbox: X)
    LEFT_TRIGGER_1,   // Gamepad top/back trigger left (first), it could be a trailing button
    LEFT_TRIGGER_2,   // Gamepad top/back trigger left (second), it could be a trailing button
    RIGHT_TRIGGER_1,  // Gamepad top/back trigger right (first), it could be a trailing button
    RIGHT_TRIGGER_2,  // Gamepad top/back trigger right (second), it could be a trailing button
    MIDDLE_LEFT,      // Gamepad center buttons, left one (i.e. PS3: Select)
    MIDDLE,           // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
    MIDDLE_RIGHT,     // Gamepad center buttons, right one (i.e. PS3: Start)
    LEFT_THUMB,       // Gamepad joystick pressed button left
    RIGHT_THUMB,      // Gamepad joystick pressed button right

    // Gamepad joystick
    LEFT_JOYSTICK_UP = CUSTOM_ID + 0,     // Gamepad joystick up (i.e. PS3: L3)
    LEFT_JOYSTICK_RIGHT = CUSTOM_ID + 1,  // Gamepad joystick right (i.e. PS3: L3)
    LEFT_JOYSTICK_DOWN = CUSTOM_ID + 2,   // Gamepad joystick down (i.e. PS3: L3)
    LEFT_JOYSTICK_LEFT = CUSTOM_ID + 3,   // Gamepad joystick left (i.e. PS3: L3)
    RIGHT_JOYSTICK_UP = CUSTOM_ID + 4,    // Gamepad joystick up (i.e. PS3: R3)
    RIGHT_JOYSTICK_RIGHT = CUSTOM_ID + 5, // Gamepad joystick right (i.e. PS3: R3)
    RIGHT_JOYSTICK_DOWN = CUSTOM_ID + 6,  // Gamepad joystick down (i.e. PS3: R3)
    RIGHT_JOYSTICK_LEFT = CUSTOM_ID + 7,  // Gamepad joystick left (i.e. PS3: R3)
    LEFT_TRIGGER = CUSTOM_ID + 8,         // Gamepad left trigger (i.e. PS3: L2)
    RIGHT_TRIGGER = CUSTOM_ID + 9,        // Gamepad right trigger (i.e. PS3: R2)
};

enum class Navigation
{
    NONE = 0,
    UP,
    RIGHT,
    DOWN,
    LEFT,
    SELECT,
    BACK,
    PAUSE,
};

class InputManager
{
private:
    static bool isNavigationEnabled;
    static Button *selectedButton;

    static std::function<void(int)> pauseCallback;
    static std::function<void(KeyboardAndMouse)> keyboardAndMouseAnyButtonCallback;
    static std::function<void(GamePad)> gamePadAnyButtonCallback;

    static Vector2 previousMousePosition;

    static std::array<bool, MAX_GAMEPADS> isGamepadLeftStickUpPressed;
    static std::array<bool, MAX_GAMEPADS> isGamepadLeftStickRightPressed;
    static std::array<bool, MAX_GAMEPADS> isGamepadLeftStickDownPressed;
    static std::array<bool, MAX_GAMEPADS> isGamepadLeftStickLeftPressed;

    static std::array<bool, MAX_GAMEPADS> isGamepadRightStickUpPressed;
    static std::array<bool, MAX_GAMEPADS> isGamepadRightStickRightPressed;
    static std::array<bool, MAX_GAMEPADS> isGamepadRightStickDownPressed;
    static std::array<bool, MAX_GAMEPADS> isGamepadRightStickLeftPressed;

    static std::array<bool, MAX_GAMEPADS> isGamepadLeftTriggerPressed;
    static std::array<bool, MAX_GAMEPADS> isGamepadRightTriggerPressed;

public:
    static void
    Init();
    static void Update();
    static void Unload();

    static void SetNavigationEnabled(bool enable);

    static void SetSelectedItem(Button *button);
    static void RemoveSelectedItem();

    static void SetPauseCallback(std::function<void(int)> callback);
    static void RemovePauseCallback();

    static void SetKeyboardAndMouseAnyButtonCallback(std::function<void(KeyboardAndMouse)> callback);
    static void RemoveKeyboardAndMouseAnyButtonCallback();
    static void SetGamePadAnyButtonCallback(std::function<void(GamePad)> callback);
    static void RemoveGamePadAnyButtonCallback();

    static float IsKeyboardAndMousePressed(KeyboardAndMouse key, float sensitivity = 1.0f);
    static float IsKeyboardAndMouseDown(KeyboardAndMouse key, float sensitivity = 1.0f);
    static float IsGamePadPressed(GamePad key, int gamepad, float threshold = 0.0f);
    static float IsGamePadDown(GamePad key, int gamepad, float threshold = 0.0f);
};