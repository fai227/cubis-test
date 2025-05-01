#include "debug.hpp"
#include "raylib.h"
#include "setting.hpp"
#include "constants.hpp"
#include "input.hpp"

void DebugManager::Init()
{
}

void DebugManager::Update()
{
    // FPS
    DrawFPS(10, 10);

    bool isCursorDownPressed = InputManager::IsKeyboardAndMousePressed(KeyboardAndMouse::MOUSE_CURSOR_DOWN);
    bool isCursorUpPressed = InputManager::IsKeyboardAndMousePressed(KeyboardAndMouse::MOUSE_CURSOR_UP);
    bool isCursorLeftPressed = InputManager::IsKeyboardAndMousePressed(KeyboardAndMouse::MOUSE_CURSOR_LEFT);
    bool isCursorRightPressed = InputManager::IsKeyboardAndMousePressed(KeyboardAndMouse::MOUSE_CURSOR_RIGHT);

    // 結果を表示
    DrawText(TextFormat("Cursor Down: %d", isCursorDownPressed), 10, 30, 20, WHITE);
    DrawText(TextFormat("Cursor Up: %d", isCursorUpPressed), 10, 50, 20, WHITE);
    DrawText(TextFormat("Cursor Left: %d", isCursorLeftPressed), 10, 70, 20, WHITE);
    DrawText(TextFormat("Cursor Right: %d", isCursorRightPressed), 10, 90, 20, WHITE);
}

void DebugManager::Unload()
{
}