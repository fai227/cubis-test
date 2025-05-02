#include "render.hpp"
#include "setting.hpp"
#include "constants.hpp"
#include "scene.hpp"
#include "raylib.h"
#include "modal.hpp"
#include "system.hpp"

#include "debug.hpp"

bool RenderManager::isTransitioning;
float RenderManager::transitionTimeLeft;
Scene *RenderManager::currentScene;
Scene *RenderManager::nextScene;
RenderTexture2D RenderManager::currentSceneTexture;
RenderTexture2D RenderManager::nextSceneTexture;

Rectangle RenderManager::CalculateScreenBounds()
{
    float currentRatio = (float)GetScreenWidth() / (float)GetScreenHeight();
    Rectangle gameScreen;
    if (currentRatio > Constants::ASPECT_RATIO) // 横長
    {
        float screenHeight = (float)GetScreenHeight();
        gameScreen = {(GetScreenWidth() - (screenHeight * Constants::ASPECT_RATIO)) / 2.0f, 0, screenHeight * (16.0f / 9.0f), screenHeight};
    }
    else // 縦長
    {
        float screenWidth = (float)GetScreenWidth();
        gameScreen = {0, (GetScreenHeight() - (screenWidth / Constants::ASPECT_RATIO)) / 2.0f, screenWidth, screenWidth * (9.0f / 16.0f)};
    }
    return gameScreen;
}

void RenderManager::Init()
{
    DebugManager::Init();

    // 初期設定
    isTransitioning = false;
    currentScene = new BlankScene();
    RenderManager::TransitToNextScene(new TitleScene());

    // テクスチャ作成
    Rectangle gameScreen = CalculateScreenBounds();
    currentSceneTexture = LoadRenderTexture(gameScreen.width, gameScreen.height);
    nextSceneTexture = LoadRenderTexture(gameScreen.width, gameScreen.height);

    // リサイズ時のコールバック登録
    SystemManager::SetWindowResizeCallback([](int width, int height)
                                           {
        UnloadRenderTexture(currentSceneTexture);
        UnloadRenderTexture(nextSceneTexture);
        currentSceneTexture = LoadRenderTexture(width, height);
        nextSceneTexture = LoadRenderTexture(width, height); });
}

void RenderManager::Update()
{
    // 描画開始処理
    Rectangle gameScreen = CalculateScreenBounds();

    // 次のシーン描画
    if (isTransitioning)
    {
        BeginTextureMode(nextSceneTexture);
        ClearBackground(SettingManager::GetColor(ColorPallet::Sub));
        nextScene->Update({gameScreen.width, gameScreen.height});
        EndTextureMode();
    }

    // 現在シーン描画
    BeginTextureMode(currentSceneTexture);
    currentScene->Update({gameScreen.width, gameScreen.height});
    EndTextureMode();

    // 画面描画
    BeginDrawing();
    ClearBackground(SettingManager::GetColor(ColorPallet::Main));
    if (isTransitioning)
    {
        float transitionRatio = transitionTimeLeft / Constants::TRANSITION_DURATION;
        float transitionWidth = gameScreen.width * transitionRatio;

        DrawTextureRec(currentSceneTexture.texture, (Rectangle){0, 0, gameScreen.width, -gameScreen.height}, (Vector2){gameScreen.x, gameScreen.y}, WHITE);
        DrawTextureRec(nextSceneTexture.texture, (Rectangle){transitionWidth, 0, gameScreen.width - transitionWidth, -gameScreen.height}, (Vector2){gameScreen.x + transitionWidth, gameScreen.y}, WHITE);

        float transitionBoundaryX = gameScreen.x + transitionWidth;
        DrawRectangle(transitionBoundaryX - 15, gameScreen.y, 30, gameScreen.height, SettingManager::GetColor(ColorPallet::Main));
    }
    else
    {
        DrawTextureRec(currentSceneTexture.texture, (Rectangle){0, 0, gameScreen.width, -gameScreen.height}, (Vector2){gameScreen.x, gameScreen.y}, WHITE);
    }

    // モーダル描画
    if (ModalManager::ModalExists())
    {
        Modal *modal = ModalManager::GetFirstModal();
        modal->Draw();
    }

    // デバッグ要素描画
    DebugManager::Update();

    // 描画終了処理
    EndDrawing();
    if (isTransitioning) // トランジション終了処理
    {
        transitionTimeLeft -= GetFrameTime();
        if (transitionTimeLeft <= 0.0f)
        {
            delete currentScene;
            nextScene->Enable();

            currentScene = nextScene;
            nextScene = nullptr;

            isTransitioning = false;
            transitionTimeLeft = Constants::TRANSITION_DURATION;
        }
    }
}

void RenderManager::Unload()
{
    DebugManager::Unload();
}

void RenderManager::TransitToNextScene(Scene *scene)
{
    isTransitioning = true;
    transitionTimeLeft = Constants::TRANSITION_DURATION;
    nextScene = scene;
}