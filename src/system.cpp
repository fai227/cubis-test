#include "system.hpp"
#include "raylib.h"
#include "constants.hpp"

void SystemManager::Init()
{
    // ウィンドウ作成
    InitWindow(DefaultSetting::DEFAULT_WINDOW_SIZE.x, DefaultSetting::DEFAULT_WINDOW_SIZE.y, DisplayText::GAME_TITLE.c_str());
    SetExitKey(0);
}

void SystemManager::Update()
{
}

void SystemManager::Unload()
{
    CloseWindow();
}