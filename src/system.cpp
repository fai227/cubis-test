#include "system.hpp"
#include "raylib.h"
#include "constants.hpp"
#include <functional>

int SystemManager::previousWidth = 0;
int SystemManager::previousHeight = 0;
std::function<void(int, int)> SystemManager::windowResizeCallback = nullptr;

void SystemManager::Init()
{
    // ウィンドウ作成
    InitWindow(DefaultSetting::DEFAULT_WINDOW_SIZE.x, DefaultSetting::DEFAULT_WINDOW_SIZE.y, DisplayText::GAME_TITLE_WITH_VERSION.c_str());
    SetWindowMinSize(Constants::MANIMUM_WINDOW_WIDTH, Constants::MANIMUM_WINDOW_HEIGHT);
    SetExitKey(0);

    // マウスカーソル非表示
    DisableCursor();
}

void SystemManager::Update()
{
    // ウィンドウサイズ変更時のコールバック処理
    if (GetScreenWidth() != previousWidth || GetScreenHeight() != previousHeight)
    {
        previousWidth = GetScreenWidth();
        previousHeight = GetScreenHeight();
        if (windowResizeCallback)
        {
            windowResizeCallback(previousWidth, previousHeight);
        }
    }
}

void SystemManager::Unload()
{
    CloseWindow();
}

void SystemManager::SetWindowResizeCallback(std::function<void(int, int)> callback)
{
    windowResizeCallback = callback;
}