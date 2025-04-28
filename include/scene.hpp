#pragma once

#include "raylib.h"

class Scene
{
public:
    virtual void Init() {}
    virtual void Start() {}
    virtual void Update() {}
    virtual void Pause() {}
    virtual void End() {}
    virtual void Unload() {}
};

class SceneManager
{
public:
    static bool isTransitioning;
    static Scene *currentScene;
    static Scene *nextScene;

    static void Update(Rectangle target);
};