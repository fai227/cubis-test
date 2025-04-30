#pragma once

#include "raylib.h"
#include <string>

class UIElement
{
protected:
    Rectangle bounds;

public:
    bool isVisible;
    bool isEnabled;
    virtual void Draw() {};
};

class Text : public UIElement
{
private:
    std::string label;

public:
    Text(Rectangle, std::string);
    void Draw() override;
};

class Button : public UIElement
{
private:
    std::string label;

public:
    bool isVisible;
    bool isEnabled;
    bool isSelected;

    Button *up;
    Button *down;
    Button *left;
    Button *right;

    Button(Rectangle, std::string);
    void Draw() override;
    void SetNavigation(Button *up, Button *down, Button *left, Button *right);
};