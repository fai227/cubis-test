#pragma once
#include "scene.hpp"
#include "raylib.h"

class RenderManager
{
private:
    static RenderTexture2D currentSceneTexture;
    static RenderTexture2D nextSceneTexture;
    static Rectangle CalculateScreenBounds();

    static bool shouldCloseWindow;

public:
    static bool isTransitioning;
    static float transitionTimeLeft;
    static Scene *currentScene;
    static Scene *nextScene;

    static void Init();
    static void Update();
    static void Unload();

    static void TransitToNextScene(Scene *scene);
};