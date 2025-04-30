#include "render.hpp"
#include "setting.hpp"
#include "constants.hpp"
#include "scene.hpp"
#include "raylib.h"
#include "modal.hpp"

bool RenderManager::isTransitioning;
Scene *RenderManager::currentScene;
Scene *RenderManager::nextScene;

Rectangle RenderManager::CalculateScreenBounds()
{
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
    return gameScreen;
}

void RenderManager::Init()
{
    isTransitioning = false;

    currentScene = new BlankScene();
    nextScene = new TitleScene();
}

void RenderManager::Update()
{
    // 描画開始処理
    BeginDrawing();

    // 背景初期化処理
    ClearBackground(SettingManager::GetColor(ColorPallet::Sub));

    // ゲーム画面位置特定
    Rectangle gameScreen = CalculateScreenBounds();

    // 次のシーン描画
    /*
    if (isTransitioning)
    {
        RenderTexture2D target = LoadRenderTexture(gameScreen.width, gameScreen.height);
        BeginTextureMode(target);
        ClearBackground(SettingManager::GetColor(ColorPallet::Sub));
        nextScene.Update();
        EndTextureMode();
        DrawTextureRec(target.texture, (Rectangle){0, 0, gameScreen.width, -gameScreen.height}, (Vector2){gameScreen.x, gameScreen.y}, WHITE);
    }
    */

    // 現在シーン描画
    currentScene->Update();

    // モーダル描画
    /*
    if (ModalManager::ModalExists())
    {
        Modal *modal = ModalManager::GetFirstModal();
        modal->Draw();
    }
    */

    // 描画終了処理
    EndDrawing();
}

void RenderManager::Unload()
{
}