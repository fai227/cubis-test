#pragma once

#include "raylib.h"
#include <string>
#include <functional>

class UIElement
{
protected:
    Rectangle bounds;

public:
    bool isVisible;
    UIElement();
    virtual void Draw(Vector2 size) {};
};

class Text : public UIElement
{
private:
    std::string label;

public:
    Text(Rectangle _bounds, std::string _label);
    void Draw(Vector2 size) override;
    void ChangeText(std::string _label);
};

class Button : public UIElement
{
private:
    std::string label;

public:
    bool isEnabled;
    bool isSelected;

    std::function<void()> OnClick = nullptr;

    Button *up = nullptr;
    Button *down = nullptr;
    Button *left = nullptr;
    Button *right = nullptr;

    Button(Rectangle _bounds, std::string _label);
    void Draw(Vector2 size) override;
    void SetNavigation(Button *_up, Button *_down, Button *_left, Button *_right);
};

namespace UI
{
    Rectangle GetScreenBounds(Vector2 size, Rectangle bounds);
    void DrawTextInsideRectangle(Rectangle bounds, std::string text, Color color);
}