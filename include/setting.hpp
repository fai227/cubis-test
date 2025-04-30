#pragma once

#include "rini.h"
#include <string>
#include "raylib.h"

enum class WindowMode
{
    Windowed = 1,
    Borderless = 2,
};

enum class Theme
{
    Light = 1,
    Dark = 2,
};

enum class ColorPallet
{
    Main,
    Sub,
    Green,
    Red,
    Blue,
    Orange,
    Purple,
    Yellow,
    Cyan,
};

class SettingManager
{
private:
    static rini_config config;

    static void SaveConfig();

public:
    static void Init();
    static void Update();
    static void Unload();

    static void SetTheme(Theme);
    static Theme GetTheme();
    static Color GetColor(ColorPallet);

    static WindowMode GetWindowMode();
    static void SetWindowMode(WindowMode);

    static int GetMonitorID();
    static void SetMonitorID(int);

    static int GetMaxFPS();
    static void SetMaxFPS(int);

    static void UpdateWindow();
    static void UpdateMaxFPS();
};
