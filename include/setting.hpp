#pragma once

#include "rini.h"
#include <string>
#include "raylib.h"

enum class WindowMode
{
    Windowed = 1,
    Borderless = 2,
    Count = 3,
};

enum class Theme
{
    Light = 1,
    Dark = 2,
    Count = 3,
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
    static WindowMode GetNextWindowMode(bool isNext);
    static void SetWindowMode(WindowMode windowMode);

    static int GetMonitorID();
    static int GetNextMonitorID(bool isNext);
    static void SetMonitorID(int monitorID);

    static int GetMaxFPS();
    static int GetNextMaxFPS(bool isNext);
    static void SetMaxFPS(int targetFPS);

    static int GetGeneralSensitivity();
    static int GetNextGeneralSensitivity(bool isNext);
    static void SetGeneralSensitivity(int sensitivity);
    static float GetGeneralSensitivityFloat();

    static int GetGeneralThreshold();
    static int GetNextGeneralThreshold(bool isNext);
    static void SetGeneralThreshold(int threshold);
    static float GetGeneralThresholdFloat();

    static void UpdateWindow();
    static void UpdateMaxFPS();

    static std::string ConvertWindowModeToString(WindowMode windowMode);
    static std::string ConvertMonitorIDToString(int monitorID);
    static std::string ConvertMaxFPSToString(int maxFPS);
    static std::string ConvertGeneralSensitivityToString(int sensitivity);
    static std::string ConvertGeneralThresholdToString(int threshold);

    static ColorPallet GetPlayerColor(int playerID);
};
