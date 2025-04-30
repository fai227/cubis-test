#pragma once

#include <vector>
#include "ui.hpp"
#include "raylib.h"

class Scene
{
protected:
    std::vector<UIElement *> uiElements;

public:
    virtual void Enable() {}
    virtual void Update(Vector2 size);
    virtual void Disable() {}
    virtual ~Scene();
};

class BlankScene : public Scene
{
public:
    BlankScene();
};

class TitleScene : public Scene
{
public:
    TitleScene();
};

class MenuScene : public Scene
{
public:
    MenuScene();
};

class GameScene : public Scene
{
public:
    GameScene();
};