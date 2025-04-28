#include "setting.hpp"
#include "rini.h"
#include "constants.hpp"

rini_config Setting::config;

void Setting::SaveConfig()
{
    rini_save_config(config, DisplayText::CONFIG_FILE_NAME);
}
void Setting::Init()
{
    config = rini_load_config(DisplayText::CONFIG_FILE_NAME);

    UpdateWindow();
    UpdateMaxFPS();
}

void Setting::SetTheme(Theme theme)
{
    rini_set_config_value(&config, DisplayText::THEME, static_cast<int>(theme), NULL);
    SaveConfig();
}

Theme Setting::GetTheme()
{
    int theme = rini_get_config_value(config, DisplayText::THEME);
    if (theme == 0)
        return DefaultSetting::DEFAULT_THEME;
    return static_cast<Theme>(theme);
}

Color Setting::GetColor(ColorPallet colorPallet)
{
    if (Setting::GetTheme() == Theme::Light)
    {
        switch (colorPallet)
        {
        case ColorPallet::Main:
            return GameColor::LIGHT_MAIN;
        case ColorPallet::Sub:
            return GameColor::LIGHT_SUB;
        case ColorPallet::Green:
            return GameColor::LIGHT_GREEN;
        case ColorPallet::Red:
            return GameColor::LIGHT_RED;
        case ColorPallet::Blue:
            return GameColor::LIGHT_BLUE;
        case ColorPallet::Orange:
            return GameColor::LIGHT_ORANGE;
        case ColorPallet::Purple:
            return GameColor::LIGHT_PURPLE;
        case ColorPallet::Yellow:
            return GameColor::LIGHT_YELLOW;
        case ColorPallet::Cyan:
            return GameColor::LIGHT_CYAN;
        }
    }

    if (Setting::GetTheme() == Theme::Dark)
    {
        switch (colorPallet)
        {
        case ColorPallet::Main:
            return GameColor::DARK_MAIN;
        case ColorPallet::Sub:
            return GameColor::DARK_SUB;
        case ColorPallet::Green:
            return GameColor::DARK_GREEN;
        case ColorPallet::Red:
            return GameColor::DARK_RED;
        case ColorPallet::Blue:
            return GameColor::DARK_BLUE;
        case ColorPallet::Orange:
            return GameColor::DARK_ORANGE;
        case ColorPallet::Purple:
            return GameColor::DARK_PURPLE;
        case ColorPallet::Yellow:
            return GameColor::DARK_YELLOW;
        case ColorPallet::Cyan:
            return GameColor::DARK_CYAN;
        }
    }

    return BLANK;
}

WindowMode Setting::GetWindowMode()
{
    int windowMode = rini_get_config_value(config, DisplayText::WINDOW_MODE);
    if (windowMode == 0)
        return DefaultSetting::DEFAULT_WINDOW_MODE;
    return static_cast<WindowMode>(windowMode);
}

void Setting::SetWindowMode(WindowMode windowMode)
{
    rini_set_config_value(&config, DisplayText::WINDOW_MODE, static_cast<int>(windowMode), NULL);
    SaveConfig();

    UpdateWindow();
}

int Setting::GetMonitorID()
{
    int monitorID = rini_get_config_value(config, DisplayText::MONITOR_ID);
    if (monitorID == 0)
        return DefaultSetting::DEFAULT_MONITOR_ID;
    return monitorID;
}

void Setting::SetMonitorID(int monitorID)
{
    rini_set_config_value(&config, DisplayText::MONITOR_ID, monitorID, NULL);
    SaveConfig();

    UpdateWindow();
}

int Setting::GetMaxFPS()
{
    int targetFPS = rini_get_config_value(config, DisplayText::MAX_FPS);
    if (targetFPS == 0)
        return DefaultSetting::DEFAULT_MAX_FPS;
    return targetFPS;
}

void Setting::SetMaxFPS(int targetFPS)
{
    rini_set_config_value(&config, DisplayText::MAX_FPS, targetFPS, NULL);
    SaveConfig();

    UpdateMaxFPS();
}

void Setting::UpdateWindow()
{
    int monitorID = Setting::GetMonitorID() - 1;
    Vector2 monitorPosition = GetMonitorPosition(monitorID);
    int monitorWidth = GetMonitorWidth(monitorID);
    int monitorHeight = GetMonitorHeight(monitorID);

    switch (Setting::GetWindowMode())
    {
    case WindowMode::Windowed:
        ClearWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED);
        SetWindowSize(DefaultSetting::DEFAULT_WINDOW_SIZE.x, DefaultSetting::DEFAULT_WINDOW_SIZE.y);
        SetWindowPosition(monitorPosition.x + (monitorWidth - DefaultSetting::DEFAULT_WINDOW_SIZE.x) / 2,
                          monitorPosition.y + (monitorHeight - DefaultSetting::DEFAULT_WINDOW_SIZE.y) / 2);
        SetWindowState(FLAG_WINDOW_RESIZABLE);
        break;

    case WindowMode::Borderless:
        ClearWindowState(FLAG_WINDOW_RESIZABLE);
        SetWindowSize(monitorWidth, monitorHeight);
        SetWindowPosition(monitorPosition.x, monitorPosition.y);
        SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED);
        break;
    }
}

void Setting::UpdateMaxFPS()
{
    SetTargetFPS(Setting::GetMaxFPS());
}