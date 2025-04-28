#pragma once

#include "raylib.h"

class UIElement
{
protected:
    Rectangle bounds;

public:
    bool isVisible;
    bool isEnabled;
    virtual void Draw(RenderTexture2D target) = 0;
};

class Text : public UIElement
{
private:
    char *label;

public:
    Text(Rectangle, char *);
    void Draw(RenderTexture2D target) override;
};

class Button : public UIElement
{
private:
    char *label;

public:
    bool isVisible;
    bool isEnabled;
    bool isSelected;

    Button *navigationUp;
    Button *navigationDown;
    Button *navigationLeft;
    Button *navigationRight;

    Button(Rectangle, char *, Button *, Button *, Button *, Button *);
    void Draw(RenderTexture2D target) override;
};