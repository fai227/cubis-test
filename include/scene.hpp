#pragma once

#include <vector>
#include "ui.hpp"
#include "raylib.h"

class Scene
{
protected:
    std::vector<UIElement *> uiElements;

public:
    Scene();
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
    void Enable() override;
};

class MenuScene : public Scene
{
public:
    MenuScene();
    void Enable() override;
};

class LeaderboardScene : public Scene
{
public:
    LeaderboardScene();
    void Enable() override;
};

class OptionScene : public Scene
{
public:
    OptionScene();
    void Enable() override;
};

class GameScene : public Scene
{
};