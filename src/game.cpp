#define RINI_IMPLEMENTATION

#include "raylib.h"
#include "game.hpp"
#include "setting.hpp"
#include "constants.hpp"
#include "scene.hpp"
#include "modal.hpp"

void Game::Init()
{
    // ウィンドウ作成
    InitWindow(DefaultSetting::DEFAULT_WINDOW_SIZE.x, DefaultSetting::DEFAULT_WINDOW_SIZE.y, DisplayText::GAME_TITLE);
    SetExitKey(0);

    // 設定の初期化
    Setting::Init();
}

void Game::Mainloop()
{
    while (!WindowShouldClose())
    {
        // 描画開始処理
        BeginDrawing();

        // 背景初期化処理
        ClearBackground(Setting::GetColor(ColorPallet::Sub));

        // ゲーム画面位置特定
        float currentRatio = (float)GetScreenWidth() / (float)GetScreenHeight();
        Rectangle gameScreen;
        if (currentRatio > (16.0f / 9.0f)) // 横長
        {
            float screenHeight = (float)GetScreenHeight();
            gameScreen = {(GetScreenWidth() - (screenHeight * (16.0f / 9.0f))) / 2.0f, 0, screenHeight * (16.0f / 9.0f), screenHeight};
        }
        else // 縦長
        {
            float screenWidth = (float)GetScreenWidth();
            gameScreen = {0, (GetScreenHeight() - (screenWidth * (9.0f / 16.0f))) / 2.0f, screenWidth, screenWidth * (9.0f / 16.0f)};
        }

        // ゲーム画面の描画
        SceneManager::Update(gameScreen);

        // 描画終了処理
        EndDrawing();
    }
}

void Game::Close()
{
    CloseWindow();
}

void Game::Run()
{
    Init();
    Mainloop();
    Close();
}
