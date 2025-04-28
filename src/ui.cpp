#include "ui.hpp"
#include "raylib.h"

Text::Text(Rectangle _bounds, char *_label)
{
    bounds = _bounds;
    label = _label;
};

void Text::Draw(RenderTexture2D target)
{
    DrawText(label, bounds.x, bounds.y, 20, WHITE);
}

Button::Button(Rectangle _bounds, char *_label, Button *_navigationUp, Button *_navigationDown, Button *_navigationLeft, Button *_navigationRight)
{
    bounds = _bounds;
    label = _label;
    navigationUp = _navigationUp;
    navigationDown = _navigationDown;
    navigationLeft = navigationLeft;
    navigationRight = navigationRight;
}

void Button::Draw(RenderTexture2D target)
{
    if (isSelected)
    {
        DrawRectangleRec(bounds, BLUE);
    }
    else
    {
        DrawRectangleRec(bounds, GRAY);
    }

    DrawText(label, bounds.x + 10, bounds.y + 10, 20, WHITE);
}