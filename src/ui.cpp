#include "ui.hpp"
#include <string>

#include "raylib.h"

Text::Text(Rectangle _bounds, std::string _label)
{
    bounds = _bounds;
    label = _label;
};

void Text::Draw()
{
    DrawText(label.c_str(), bounds.x, bounds.y, 20, WHITE);
}

Button::Button(Rectangle _bounds, std::string _label)
{
    bounds = _bounds;
    label = _label;
}

void Button::SetNavigation(Button *_up, Button *_down, Button *_left, Button *_right)
{
    up = _up;
    down = _down;
    left = _left;
    right = _right;
}

void Button::Draw()
{
    if (isSelected)
    {
        DrawRectangleRec(bounds, BLUE);
    }
    else
    {
        DrawRectangleRec(bounds, GRAY);
    }

    DrawText(label.c_str(), bounds.x + 10, bounds.y + 10, 20, WHITE);
}