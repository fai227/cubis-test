#include "ui.hpp"
#include <string>
#include "raylib.h"
#include "constants.hpp"
#include "setting.hpp"

UIElement::UIElement()
{
    isVisible = true;
}

Text::Text(Rectangle _bounds, std::string _label)
{
    bounds = _bounds;
    label = _label;
};

void Text::Draw(Vector2 size)
{
    Rectangle realBounds = UI::GetScreenBounds(size, bounds);
    // DrawRectangleRec(realBounds, RED); // デバッグ用赤枠で囲う
    UI::DrawTextInsideRectangle(realBounds, label, SettingManager::GetColor(ColorPallet::Main));
}

void Text::ChangeText(std::string _label)
{
    label = _label;
}

Button::Button(Rectangle _bounds, std::string _label)
{
    isEnabled = true;
    isSelected = false;

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

void Button::Draw(Vector2 size)
{
    if (!isVisible)
        return;

    Rectangle realBounds = UI::GetScreenBounds(size, bounds);

    if (!isEnabled)
    {
        DrawRectangleRec(realBounds, SettingManager::GetColor(ColorPallet::Glay));
        UI::DrawTextInsideRectangle(realBounds, label, SettingManager::GetColor(ColorPallet::Main));
        return;
    }

    if (isSelected)
    {
        DrawRectangleLines(realBounds.x, realBounds.y, realBounds.width, realBounds.height, SettingManager::GetColor(ColorPallet::Main));
        DrawRectangle(realBounds.x + 2, realBounds.y + 2, realBounds.width - 4, realBounds.height - 4, SettingManager::GetColor(ColorPallet::Main));
        UI::DrawTextInsideRectangle(realBounds, label, SettingManager::GetColor(ColorPallet::Sub));
        return;
    }

    DrawRectangleLines(realBounds.x, realBounds.y, realBounds.width, realBounds.height, SettingManager::GetColor(ColorPallet::Main));
    UI::DrawTextInsideRectangle(realBounds, label, SettingManager::GetColor(ColorPallet::Main));
}

Rectangle UI::GetScreenBounds(Vector2 size, Rectangle bounds)
{
    float rectWidth = bounds.width * size.x;
    float rectHeight = bounds.height * size.y;
    float rectX = (bounds.x - bounds.width * 0.5f) * size.x;
    float rectY = (bounds.y - bounds.height * 0.5f) * size.y;

    return {rectX, rectY, rectWidth, rectHeight};
}

void UI::DrawTextInsideRectangle(Rectangle bounds, std::string text, Color color)
{
    int fontSize = bounds.height;
    Vector2 textSize;

    while (fontSize > 1)
    {
        textSize = MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, fontSize / 10.0f);
        if (textSize.x < bounds.width * Constants::MAX_TEXT_SIZE_IN_BOUNDS && textSize.y < bounds.height * Constants::MAX_TEXT_SIZE_IN_BOUNDS)
            break;
        fontSize--;
    }

    Vector2 textPosition = {bounds.x + (bounds.width - textSize.x) / 2, bounds.y + (bounds.height - textSize.y) / 2};
    DrawTextEx(GetFontDefault(), text.c_str(), textPosition, fontSize, fontSize / 10.0f, color);
}