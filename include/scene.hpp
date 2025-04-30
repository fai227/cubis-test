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
    virtual void Update();
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
};

class GameScene : public Scene
{
};