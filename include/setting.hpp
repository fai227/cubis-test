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
    Glay,
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

    static void SetTheme(Theme theme);
    static Theme GetTheme();
    static Color GetColor(ColorPallet colorPallet);

    static WindowMode GetWindowMode();
    static void SetWindowMode(WindowMode windowMode);

    static int GetMonitorID();
    static void SetMonitorID(int monitorID);

    static int GetMaxFPS();
    static void SetMaxFPS(int targetFPS);

    static void UpdateWindow();
    static void UpdateMaxFPS();
};
