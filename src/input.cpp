#include "input.hpp"
#include "ui.hpp"
#include <functional>
#include "util.hpp"
#include <algorithm>

bool InputManager::isNavigationEnabled = false;
Button *InputManager::selectedButton = nullptr;

std::function<void(int)> InputManager::pauseCallback = nullptr;
std::function<void(KeyboardAndMouse)> InputManager::keyboardAndMouseAnyButtonCallback = nullptr;
std::function<void(GamePad)> InputManager::gamePadAnyButtonCallback = nullptr;

Vector2 InputManager::previousMousePosition = {0, 0};

std::array<bool, MAX_GAMEPADS> InputManager::isGamepadLeftStickUpPressed = {};
std::array<bool, MAX_GAMEPADS> InputManager::isGamepadLeftStickRightPressed = {};
std::array<bool, MAX_GAMEPADS> InputManager::isGamepadLeftStickDownPressed = {};
std::array<bool, MAX_GAMEPADS> InputManager::isGamepadLeftStickLeftPressed = {};

std::array<bool, MAX_GAMEPADS> InputManager::isGamepadRightStickUpPressed = {};
std::array<bool, MAX_GAMEPADS> InputManager::isGamepadRightStickRightPressed = {};
std::array<bool, MAX_GAMEPADS> InputManager::isGamepadRightStickDownPressed = {};
std::array<bool, MAX_GAMEPADS> InputManager::isGamepadRightStickLeftPressed = {};

std::array<bool, MAX_GAMEPADS> InputManager::isGamepadLeftTriggerPressed = {};
std::array<bool, MAX_GAMEPADS> InputManager::isGamepadRightTriggerPressed = {};

void InputManager::Init()
{
}

void InputManager::Update()
{
}

void InputManager::Unload()
{
}

void InputManager::SetNavigationEnabled(bool enable)
{
}

void InputManager::SetSelectedItem(Button *button)
{
    if (selectedButton != nullptr)
    {
        selectedButton->isSelected = false;
    }

    selectedButton = button;
    selectedButton->isSelected = true;
}

void InputManager::RemoveSelectedItem()
{
    if (selectedButton != nullptr)
    {
        selectedButton->isSelected = false;
        selectedButton = nullptr;
    }
}

void InputManager::SetPauseCallback(std::function<void(int)> callback)
{
}

void InputManager::SetKeyboardAndMouseAnyButtonCallback(std::function<void(KeyboardAndMouse)> callback)
{
}

void InputManager::RemoveKeyboardAndMouseAnyButtonCallback()
{
}

void InputManager::SetGamePadAnyButtonCallback(std::function<void(GamePad)> callback)
{
}

void InputManager::RemoveGamePadAnyButtonCallback()
{
}

float InputManager::IsKeyboardAndMousePressed(KeyboardAndMouse key, float sensitivity)
{
    int keyId = static_cast<int>(key);

    // Keyboard
    if (keyId < CUSTOM_ID)
    {
        return IsKeyPressed(static_cast<KeyboardKey>(keyId)) ? 1.0f : 0.0f;
    }

    // Mouse Buttons
    switch (key)
    {
    case KeyboardAndMouse::MOUSE_BUTTON_LEFT:
        return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_RIGHT:
        return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_MIDDLE:
        return IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_SIDE:
        return IsMouseButtonPressed(MOUSE_BUTTON_SIDE) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_EXTRA:
        return IsMouseButtonPressed(MOUSE_BUTTON_EXTRA) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_FORWARD:
        return IsMouseButtonPressed(MOUSE_BUTTON_FORWARD) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_BACK:
        return IsMouseButtonPressed(MOUSE_BUTTON_BACK) ? 1.0f : 0.0f;
    }

    // Mouse Wheel
    switch (key)
    {
    case KeyboardAndMouse::MOUSE_WHEEL_UP:
        return Utility::ReLU(GetMouseWheelMoveV().y * sensitivity);
    case KeyboardAndMouse::MOUSE_WHEEL_DOWN:
        return Utility::ReLU(-GetMouseWheelMoveV().y * sensitivity);
    case KeyboardAndMouse::MOUSE_WHEEL_LEFT:
        return Utility::ReLU(GetMouseWheelMoveV().x * sensitivity);
    case KeyboardAndMouse::MOUSE_WHEEL_RIGHT:
        return Utility::ReLU(-GetMouseWheelMoveV().x * sensitivity);
    }

    // Mouse Cursor
    float distanceX = GetScreenWidth() / sensitivity;
    float distanceY = GetScreenHeight() / sensitivity;
    Vector2 mousePosition = GetMousePosition();
    switch (key)
    {
    case KeyboardAndMouse::MOUSE_CURSOR_UP:
        if ((mousePosition.y - previousMousePosition.y) < -distanceY)
        {
            previousMousePosition.y = mousePosition.y;
            return 1.0f;
        }
        return 0.0f;

    case KeyboardAndMouse::MOUSE_CURSOR_DOWN:
        if ((mousePosition.y - previousMousePosition.y) > distanceY)
        {
            previousMousePosition.y = mousePosition.y;
            return 1.0f;
        }
        return 0.0f;

    case KeyboardAndMouse::MOUSE_CURSOR_LEFT:
        if ((mousePosition.x - previousMousePosition.x) < -distanceX)
        {
            previousMousePosition.x = mousePosition.x;
            return 1.0f;
        }
        return 0.0f;

    case KeyboardAndMouse::MOUSE_CURSOR_RIGHT:
        if ((mousePosition.x - previousMousePosition.x) > distanceX)
        {
            previousMousePosition.x = mousePosition.x;
            return 1.0f;
        }
        return 0.0f;
    }

    TraceLog(LOG_WARNING, "InputManager::IsKeyboardAndMousePressed: Invalid key ID: %d", keyId);
    return 0.0f;
}

float InputManager::IsKeyboardAndMouseDown(KeyboardAndMouse key, float sensitivity)
{
    int keyId = static_cast<int>(key);

    // keyboard
    if (keyId < CUSTOM_ID)
    {
        return IsKeyDown(static_cast<KeyboardKey>(keyId)) ? 1.0f : 0.0f;
    }

    // Mouse Buttons
    switch (key)
    {
    case KeyboardAndMouse::MOUSE_BUTTON_LEFT:
        return IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_RIGHT:
        return IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_MIDDLE:
        return IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_SIDE:
        return IsMouseButtonDown(MOUSE_BUTTON_SIDE) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_EXTRA:
        return IsMouseButtonDown(MOUSE_BUTTON_EXTRA) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_FORWARD:
        return IsMouseButtonDown(MOUSE_BUTTON_FORWARD) ? 1.0f : 0.0f;
    case KeyboardAndMouse::MOUSE_BUTTON_BACK:
        return IsMouseButtonDown(MOUSE_BUTTON_BACK) ? 1.0f : 0.0f;
    }

    // Mouse Wheel
    switch (key)
    {
    case KeyboardAndMouse::MOUSE_WHEEL_UP:
        return Utility::ReLU(GetMouseWheelMoveV().y * sensitivity);
    case KeyboardAndMouse::MOUSE_WHEEL_DOWN:
        return Utility::ReLU(-GetMouseWheelMoveV().y * sensitivity);
    case KeyboardAndMouse::MOUSE_WHEEL_LEFT:
        return Utility::ReLU(GetMouseWheelMoveV().x * sensitivity);
    case KeyboardAndMouse::MOUSE_WHEEL_RIGHT:
        return Utility::ReLU(-GetMouseWheelMoveV().x * sensitivity);
    }

    // Mouse Cursor
    switch (key)
    {
    case KeyboardAndMouse::MOUSE_CURSOR_UP:
        return Utility::ReLU(GetMouseDelta().y * sensitivity);
    case KeyboardAndMouse::MOUSE_CURSOR_DOWN:
        return Utility::ReLU(-GetMouseDelta().y * sensitivity);
    case KeyboardAndMouse::MOUSE_CURSOR_LEFT:
        return Utility::ReLU(GetMouseDelta().x * sensitivity);
    case KeyboardAndMouse::MOUSE_CURSOR_RIGHT:
        return Utility::ReLU(-GetMouseDelta().x * sensitivity);
    }

    TraceLog(LOG_WARNING, "InputManager::IsKeyboardAndMouseDown: Invalid key ID: %d", keyId);
    return 0.0f;
}

float InputManager::IsGamePadPressed(GamePad key, int gamepad, float threshold)
{
    if (!IsGamepadAvailable(gamepad))
    {
        return 0.0f;
    }

    int keyId = static_cast<int>(key);

    // Buttons
    if (keyId < CUSTOM_ID)
    {
        return IsGamepadButtonPressed(gamepad, keyId) ? 1.0f : 0.0f;
    }

    // Joysticks
    switch (key)
    {
    case GamePad::LEFT_JOYSTICK_UP:
        isGamepadLeftStickUpPressed[gamepad] = (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > threshold) && (!isGamepadLeftStickUpPressed[gamepad]);
        return isGamepadLeftStickUpPressed[gamepad] ? 1.0f : 0.0f;
    case GamePad::LEFT_JOYSTICK_DOWN:
        isGamepadLeftStickDownPressed[gamepad] = (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) < -threshold) && (!isGamepadLeftStickDownPressed[gamepad]);
        return isGamepadLeftStickDownPressed[gamepad] ? 1.0f : 0.0f;
    case GamePad::LEFT_JOYSTICK_LEFT:
        isGamepadLeftStickLeftPressed[gamepad] = (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) < -threshold) && (!isGamepadLeftStickLeftPressed[gamepad]);
        return isGamepadLeftStickLeftPressed[gamepad] ? 1.0f : 0.0f;
    case GamePad::LEFT_JOYSTICK_RIGHT:
        isGamepadLeftStickRightPressed[gamepad] = (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) > threshold) && (!isGamepadLeftStickRightPressed[gamepad]);
        return isGamepadLeftStickRightPressed[gamepad] ? 1.0f : 0.0f;

    case GamePad::RIGHT_JOYSTICK_UP:
        isGamepadRightStickUpPressed[gamepad] = (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) > threshold) && (!isGamepadRightStickUpPressed[gamepad]);
        return isGamepadRightStickUpPressed[gamepad] ? 1.0f : 0.0f;
    case GamePad::RIGHT_JOYSTICK_DOWN:
        isGamepadRightStickDownPressed[gamepad] = (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y) < -threshold) && (!isGamepadRightStickDownPressed[gamepad]);
        return isGamepadRightStickDownPressed[gamepad] ? 1.0f : 0.0f;
    case GamePad::RIGHT_JOYSTICK_LEFT:
        isGamepadRightStickLeftPressed[gamepad] = (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) < -threshold) && (!isGamepadRightStickLeftPressed[gamepad]);
        return isGamepadRightStickLeftPressed[gamepad] ? 1.0f : 0.0f;
    case GamePad::RIGHT_JOYSTICK_RIGHT:
        isGamepadRightStickRightPressed[gamepad] = (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X) > threshold) && (!isGamepadRightStickRightPressed[gamepad]);
        return isGamepadRightStickRightPressed[gamepad] ? 1.0f : 0.0f;

    case GamePad::LEFT_TRIGGER:
        isGamepadLeftTriggerPressed[gamepad] = (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER) > threshold) && (!isGamepadLeftTriggerPressed[gamepad]);
        return isGamepadLeftTriggerPressed[gamepad] ? 1.0f : 0.0f;
    case GamePad::RIGHT_TRIGGER:
        isGamepadRightTriggerPressed[gamepad] = (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER) > threshold) && (!isGamepadRightTriggerPressed[gamepad]);
        return isGamepadRightTriggerPressed[gamepad] ? 1.0f : 0.0f;
    }

    TraceLog(LOG_WARNING, "InputManager::IsGamePadPressed: Invalid key ID: %d", keyId);
    return 0.0f;
}

float InputManager::IsGamePadDown(GamePad key, int gamepad, float threshold)
{
    if (!IsGamepadAvailable(gamepad))
    {
        return 0.0f;
    }

    int keyId = static_cast<int>(key);

    // Buttons
    if (keyId < CUSTOM_ID)
    {
        return IsGamepadButtonDown(gamepad, keyId) ? 1.0f : 0.0f;
    }

    // Joysticks
    switch (key)
    {
    case GamePad::LEFT_JOYSTICK_UP:
    {
        float leftUp = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y));
        return leftUp > threshold ? leftUp : 0.0f;
    }
    case GamePad::LEFT_JOYSTICK_DOWN:
    {
        float leftDown = Utility::ReLU(-GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y));
        return leftDown > threshold ? leftDown : 0.0f;
    }
    case GamePad::LEFT_JOYSTICK_LEFT:
    {
        float leftLeft = Utility::ReLU(-GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X));
        return leftLeft > threshold ? leftLeft : 0.0f;
    }
    case GamePad::LEFT_JOYSTICK_RIGHT:
    {
        float leftRight = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X));
        return leftRight > threshold ? leftRight : 0.0f;
    }
    case GamePad::RIGHT_JOYSTICK_UP:
    {
        float rightUp = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y));
        return rightUp > threshold ? rightUp : 0.0f;
    }
    case GamePad::RIGHT_JOYSTICK_DOWN:
    {
        float rightDown = Utility::ReLU(-GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y));
        return rightDown > threshold ? rightDown : 0.0f;
    }
    case GamePad::RIGHT_JOYSTICK_LEFT:
    {
        float rightLeft = Utility::ReLU(-GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X));
        return rightLeft > threshold ? rightLeft : 0.0f;
    }
    case GamePad::RIGHT_JOYSTICK_RIGHT:
    {
        float rightRight = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X));
        return rightRight > threshold ? rightRight : 0.0f;
    }
    case GamePad::LEFT_TRIGGER:
    {
        float leftTrigger = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER));
        return leftTrigger > threshold ? leftTrigger : 0.0f;
    }
    case GamePad::RIGHT_TRIGGER:
    {
        float rightTrigger = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER));
        return rightTrigger > threshold ? rightTrigger : 0.0f;
    }
    }

    TraceLog(LOG_WARNING, "InputManager::IsGamePadDown: Invalid key ID: %d", keyId);
    return 0.0f;
}