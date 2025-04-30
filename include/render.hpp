#pragma once
#include "scene.hpp"
#include "raylib.h"

class RenderManager
{
private:
    static Rectangle CalculateScreenBounds();

public:
    static bool isTransitioning;
    static Scene *currentScene;
    static Scene *nextScene;

    static void Init();
    static void Update();
    static void Unload();
};