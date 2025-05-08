#include "input.hpp"
#include "ui.hpp"
#include <functional>
#include "util.hpp"
#include <algorithm>
#include "setting.hpp"
#include "magic_enum.hpp"
#include "constants.hpp"

bool InputManager::isNavigationEnabled = false;
Button *InputManager::selectedButton = nullptr;

std::function<void(int)> InputManager::pauseCallback = nullptr;
std::function<void(CKeyboardMouse)> InputManager::keyboardMouseAnyButtonCallback = nullptr;
std::function<void(CGamepad)> InputManager::gamePadAnyButtonCallback = nullptr;

Vector2 InputManager::previousMousePosition = {0, 0};

bool InputManager::isMouseCursorUpPressed = false;
bool InputManager::isMouseCursorDownPressed = false;
bool InputManager::isMouseCursorLeftPressed = false;
bool InputManager::isMouseCursorRightPressed = false;

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

int InputManager::GetCGamepadPressed(CGamepad key)
{
    for (int i = 0; i < MAX_GAMEPADS; i++)
    {
        if (InputManager::IsCGamepadPressed(key, i))
        {
            return i;
        }
    }
    return -1;
}

void InputManager::UpdateCInputs()
{
    // Mouse Cursor
    float sensitivity = SettingManager::GetGeneralSensitivityFloat();
    float distanceX = GetScreenWidth() / sensitivity;
    float distanceY = GetScreenHeight() / sensitivity;
    Vector2 mousePosition = GetMousePosition();

    isMouseCursorUpPressed = false;
    isMouseCursorDownPressed = false;
    isMouseCursorLeftPressed = false;
    isMouseCursorRightPressed = false;

    if (mousePosition.x - previousMousePosition.x > distanceX)
    {
        isMouseCursorRightPressed = true;
        previousMousePosition = mousePosition;
    }
    else if (mousePosition.x - previousMousePosition.x < -distanceX)
    {
        isMouseCursorLeftPressed = true;
        previousMousePosition = mousePosition;
    }
    if (mousePosition.y - previousMousePosition.y > distanceY)
    {
        isMouseCursorDownPressed = true;
        previousMousePosition = mousePosition;
    }
    else if (mousePosition.y - previousMousePosition.y < -distanceY)
    {
        isMouseCursorUpPressed = true;
        previousMousePosition = mousePosition;
    }

    // Gamepads
    for (int i = 0; i < MAX_GAMEPADS; i++)
    {
        float threshold = SettingManager::GetGeneralThresholdFloat();

        isGamepadLeftStickUpPressed[i] = (GetGamepadAxisMovement(i, GAMEPAD_AXIS_LEFT_Y) > threshold) && (!isGamepadLeftStickUpPressed[i]);
        isGamepadLeftStickRightPressed[i] = (GetGamepadAxisMovement(i, GAMEPAD_AXIS_LEFT_X) > threshold) && (!isGamepadLeftStickRightPressed[i]);
        isGamepadLeftStickDownPressed[i] = (GetGamepadAxisMovement(i, GAMEPAD_AXIS_LEFT_Y) < -threshold) && (!isGamepadLeftStickDownPressed[i]);
        isGamepadLeftStickLeftPressed[i] = (GetGamepadAxisMovement(i, GAMEPAD_AXIS_LEFT_X) < -threshold) && (!isGamepadLeftStickLeftPressed[i]);

        isGamepadRightStickUpPressed[i] = (GetGamepadAxisMovement(i, GAMEPAD_AXIS_RIGHT_Y) > threshold) && (!isGamepadRightStickUpPressed[i]);
        isGamepadRightStickRightPressed[i] = (GetGamepadAxisMovement(i, GAMEPAD_AXIS_RIGHT_X) > threshold) && (!isGamepadRightStickRightPressed[i]);
        isGamepadRightStickDownPressed[i] = (GetGamepadAxisMovement(i, GAMEPAD_AXIS_RIGHT_Y) < -threshold) && (!isGamepadRightStickDownPressed[i]);
        isGamepadRightStickLeftPressed[i] = (GetGamepadAxisMovement(i, GAMEPAD_AXIS_RIGHT_X) < -threshold) && (!isGamepadRightStickLeftPressed[i]);

        isGamepadLeftTriggerPressed[i] = (GetGamepadAxisMovement(i, GAMEPAD_AXIS_LEFT_TRIGGER) > threshold) && (!isGamepadLeftTriggerPressed[i]);
        isGamepadRightTriggerPressed[i] = (GetGamepadAxisMovement(i, GAMEPAD_AXIS_RIGHT_TRIGGER) > threshold) && (!isGamepadRightTriggerPressed[i]);
    }
}

void InputManager::UpdateUINavigation()
{
    if (!isNavigationEnabled)
    {
        return;
    }

    if (selectedButton == nullptr)
    {
        return;
    }

    if (IsCKeyboardMousePressed(CKeyboardMouse::KEY_A) || IsCKeyboardMousePressed(CKeyboardMouse::KEY_LEFT) || GetCGamepadPressed(CGamepad::LEFT_FACE_LEFT) >= 0)
    {
        if (selectedButton->left != nullptr)
        {
            InputManager::SetSelectedItem(selectedButton->left);
        }
    }

    if (IsCKeyboardMousePressed(CKeyboardMouse::KEY_D) || IsCKeyboardMousePressed(CKeyboardMouse::KEY_RIGHT) || GetCGamepadPressed(CGamepad::LEFT_FACE_RIGHT) >= 0)
    {
        if (selectedButton->right != nullptr)
        {
            InputManager::SetSelectedItem(selectedButton->right);
        }
    }

    if (IsCKeyboardMousePressed(CKeyboardMouse::KEY_W) || IsCKeyboardMousePressed(CKeyboardMouse::KEY_UP) || GetCGamepadPressed(CGamepad::LEFT_FACE_UP) >= 0)
    {
        if (selectedButton->up != nullptr)
        {
            InputManager::SetSelectedItem(selectedButton->up);
        }
    }

    if (IsCKeyboardMousePressed(CKeyboardMouse::KEY_S) || IsCKeyboardMousePressed(CKeyboardMouse::KEY_DOWN) || GetCGamepadPressed(CGamepad::LEFT_FACE_DOWN) >= 0)
    {
        if (selectedButton->down != nullptr)
        {
            InputManager::SetSelectedItem(selectedButton->down);
        }
    }

    if (IsCKeyboardMousePressed(CKeyboardMouse::KEY_ENTER) || GetCGamepadPressed(CGamepad::RIGHT_FACE_DOWN) >= 0)
    {
        if (selectedButton->OnClick != nullptr)
        {
            selectedButton->OnClick();
        }
    }
}

void InputManager::UpdatePause()
{
    if (pauseCallback == nullptr)
    {
        return;
    }

    int gamepadID = GetCGamepadPressed(CGamepad::MIDDLE_RIGHT);
    if (IsCKeyboardMousePressed(CKeyboardMouse::KEY_ESCAPE) || gamepadID >= 0)
    {
        pauseCallback(gamepadID);
    }
}

void InputManager::UpdateAnyCKeyboardMouse()
{
    if (keyboardMouseAnyButtonCallback == nullptr)
    {
        return;
    }

    for (CKeyboardMouse key : magic_enum::enum_values<CKeyboardMouse>())
    {
        if (IsCKeyboardMousePressed(key) > 0.0f)
        {
            keyboardMouseAnyButtonCallback(key);
            break;
        }
    }
}

void InputManager::UpdateAnyCGamepad()
{
    if (gamePadAnyButtonCallback == nullptr)
    {
        return;
    }

    for (CGamepad key : magic_enum::enum_values<CGamepad>())
    {
        int gamepadID = GetCGamepadPressed(key);
        if (gamepadID >= 0)
        {
            gamePadAnyButtonCallback(key);
            break;
        }
    }
}

void InputManager::Init()
{
}

void InputManager::Update()
{
    InputManager::UpdateCInputs();

    InputManager::UpdateUINavigation();
    InputManager::UpdatePause();
    InputManager::UpdateAnyCKeyboardMouse();
    InputManager::UpdateAnyCGamepad();
}

void InputManager::Unload()
{
}

void InputManager::SetNavigationEnabled(bool enable)
{
    isNavigationEnabled = enable;
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
    pauseCallback = callback;
}

void InputManager::RemovePauseCallback()
{
    pauseCallback = nullptr;
}

void InputManager::SetAnyCKeyboardMouseCallback(std::function<void(CKeyboardMouse)> callback)
{
    keyboardMouseAnyButtonCallback = callback;
}

void InputManager::RemoveAnyCKeyboardMouseCallback()
{
    keyboardMouseAnyButtonCallback = nullptr;
}

void InputManager::SetAnyCGamepadCallback(std::function<void(CGamepad)> callback)
{
    gamePadAnyButtonCallback = callback;
}

void InputManager::RemoveAnyCGamepadCallback()
{
    gamePadAnyButtonCallback = nullptr;
}

float InputManager::IsCKeyboardMousePressed(CKeyboardMouse key, float sensitivity)
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
    case CKeyboardMouse::MOUSE_BUTTON_LEFT:
        return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_RIGHT:
        return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_MIDDLE:
        return IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_SIDE:
        return IsMouseButtonPressed(MOUSE_BUTTON_SIDE) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_EXTRA:
        return IsMouseButtonPressed(MOUSE_BUTTON_EXTRA) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_FORWARD:
        return IsMouseButtonPressed(MOUSE_BUTTON_FORWARD) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_BACK:
        return IsMouseButtonPressed(MOUSE_BUTTON_BACK) ? 1.0f : 0.0f;
    }

    // Mouse Wheel
    switch (key)
    {
    case CKeyboardMouse::MOUSE_WHEEL_UP:
        return Utility::ReLU(GetMouseWheelMoveV().y * sensitivity);
    case CKeyboardMouse::MOUSE_WHEEL_DOWN:
        return Utility::ReLU(-GetMouseWheelMoveV().y * sensitivity);
    case CKeyboardMouse::MOUSE_WHEEL_LEFT:
        return Utility::ReLU(GetMouseWheelMoveV().x * sensitivity);
    case CKeyboardMouse::MOUSE_WHEEL_RIGHT:
        return Utility::ReLU(-GetMouseWheelMoveV().x * sensitivity);
    }

    // Mouse Cursor
    switch (key)
    {
    case CKeyboardMouse::MOUSE_CURSOR_UP:
        return isMouseCursorUpPressed ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_CURSOR_DOWN:
        return isMouseCursorDownPressed ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_CURSOR_LEFT:
        return isMouseCursorLeftPressed ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_CURSOR_RIGHT:
        return isMouseCursorRightPressed ? 1.0f : 0.0f;
    }

    TraceLog(LOG_WARNING, "InputManager::IsCKeyboardMousePressed: Invalid key ID: %d", keyId);
    return 0.0f;
}

float InputManager::IsCKeyboardMouseDown(CKeyboardMouse key, float sensitivity)
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
    case CKeyboardMouse::MOUSE_BUTTON_LEFT:
        return IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_RIGHT:
        return IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_MIDDLE:
        return IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_SIDE:
        return IsMouseButtonDown(MOUSE_BUTTON_SIDE) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_EXTRA:
        return IsMouseButtonDown(MOUSE_BUTTON_EXTRA) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_FORWARD:
        return IsMouseButtonDown(MOUSE_BUTTON_FORWARD) ? 1.0f : 0.0f;
    case CKeyboardMouse::MOUSE_BUTTON_BACK:
        return IsMouseButtonDown(MOUSE_BUTTON_BACK) ? 1.0f : 0.0f;
    }

    // Mouse Wheel
    switch (key)
    {
    case CKeyboardMouse::MOUSE_WHEEL_UP:
        return Utility::ReLU(GetMouseWheelMoveV().y * sensitivity);
    case CKeyboardMouse::MOUSE_WHEEL_DOWN:
        return Utility::ReLU(-GetMouseWheelMoveV().y * sensitivity);
    case CKeyboardMouse::MOUSE_WHEEL_LEFT:
        return Utility::ReLU(GetMouseWheelMoveV().x * sensitivity);
    case CKeyboardMouse::MOUSE_WHEEL_RIGHT:
        return Utility::ReLU(-GetMouseWheelMoveV().x * sensitivity);
    }

    // Mouse Cursor
    switch (key)
    {
    case CKeyboardMouse::MOUSE_CURSOR_UP:
        return Utility::ReLU(GetMouseDelta().y * sensitivity);
    case CKeyboardMouse::MOUSE_CURSOR_DOWN:
        return Utility::ReLU(-GetMouseDelta().y * sensitivity);
    case CKeyboardMouse::MOUSE_CURSOR_LEFT:
        return Utility::ReLU(GetMouseDelta().x * sensitivity);
    case CKeyboardMouse::MOUSE_CURSOR_RIGHT:
        return Utility::ReLU(-GetMouseDelta().x * sensitivity);
    }

    TraceLog(LOG_WARNING, "InputManager::IsCKeyboardMouseDown: Invalid key ID: %d", keyId);
    return 0.0f;
}

float InputManager::IsCGamepadPressed(CGamepad key, int gamepad, float threshold)
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
    case CGamepad::LEFT_JOYSTICK_UP:
        return isGamepadLeftStickUpPressed[gamepad] ? 1.0f : 0.0f;
    case CGamepad::LEFT_JOYSTICK_DOWN:
        return isGamepadLeftStickDownPressed[gamepad] ? 1.0f : 0.0f;
    case CGamepad::LEFT_JOYSTICK_LEFT:
        return isGamepadLeftStickLeftPressed[gamepad] ? 1.0f : 0.0f;
    case CGamepad::LEFT_JOYSTICK_RIGHT:
        return isGamepadLeftStickRightPressed[gamepad] ? 1.0f : 0.0f;

    case CGamepad::RIGHT_JOYSTICK_UP:
        return isGamepadRightStickUpPressed[gamepad] ? 1.0f : 0.0f;
    case CGamepad::RIGHT_JOYSTICK_DOWN:
        return isGamepadRightStickDownPressed[gamepad] ? 1.0f : 0.0f;
    case CGamepad::RIGHT_JOYSTICK_LEFT:
        return isGamepadRightStickLeftPressed[gamepad] ? 1.0f : 0.0f;
    case CGamepad::RIGHT_JOYSTICK_RIGHT:
        return isGamepadRightStickRightPressed[gamepad] ? 1.0f : 0.0f;

    case CGamepad::LEFT_TRIGGER:
        return isGamepadLeftTriggerPressed[gamepad] ? 1.0f : 0.0f;
    case CGamepad::RIGHT_TRIGGER:
        return isGamepadRightTriggerPressed[gamepad] ? 1.0f : 0.0f;
    }

    TraceLog(LOG_WARNING, "InputManager::IsCGamepadPressed: Invalid key ID: %d", keyId);
    return 0.0f;
}

float InputManager::IsCGamepadDown(CGamepad key, int gamepad, float threshold)
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
    case CGamepad::LEFT_JOYSTICK_UP:
    {
        float leftUp = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y));
        return leftUp > threshold ? leftUp : 0.0f;
    }
    case CGamepad::LEFT_JOYSTICK_DOWN:
    {
        float leftDown = Utility::ReLU(-GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y));
        return leftDown > threshold ? leftDown : 0.0f;
    }
    case CGamepad::LEFT_JOYSTICK_LEFT:
    {
        float leftLeft = Utility::ReLU(-GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X));
        return leftLeft > threshold ? leftLeft : 0.0f;
    }
    case CGamepad::LEFT_JOYSTICK_RIGHT:
    {
        float leftRight = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X));
        return leftRight > threshold ? leftRight : 0.0f;
    }
    case CGamepad::RIGHT_JOYSTICK_UP:
    {
        float rightUp = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y));
        return rightUp > threshold ? rightUp : 0.0f;
    }
    case CGamepad::RIGHT_JOYSTICK_DOWN:
    {
        float rightDown = Utility::ReLU(-GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y));
        return rightDown > threshold ? rightDown : 0.0f;
    }
    case CGamepad::RIGHT_JOYSTICK_LEFT:
    {
        float rightLeft = Utility::ReLU(-GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X));
        return rightLeft > threshold ? rightLeft : 0.0f;
    }
    case CGamepad::RIGHT_JOYSTICK_RIGHT:
    {
        float rightRight = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X));
        return rightRight > threshold ? rightRight : 0.0f;
    }
    case CGamepad::LEFT_TRIGGER:
    {
        float leftTrigger = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER));
        return leftTrigger > threshold ? leftTrigger : 0.0f;
    }
    case CGamepad::RIGHT_TRIGGER:
    {
        float rightTrigger = Utility::ReLU(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER));
        return rightTrigger > threshold ? rightTrigger : 0.0f;
    }
    }

    TraceLog(LOG_WARNING, "InputManager::IsCGamepadDown: Invalid key ID: %d", keyId);
    return 0.0f;
}

std::string InputManager::GetInputName(int inputID)
{
    if (inputID < 0)
    {
        return GameText::KEYBOARD_AND_MOUSE.c_str();
    }

    if (IsGamepadAvailable(inputID))
    {
        return GetGamepadName(inputID);
    }

    TraceLog(LOG_WARNING, "InputManager::GetInputName: Invalid input ID: %d", inputID);
    return GameText::INVALID_INPUT.c_str();
}