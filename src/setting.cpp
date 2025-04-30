#include "setting.hpp"
#include "rini.h"
#include "constants.hpp"

rini_config SettingManager::config;

void SettingManager::SaveConfig()
{
    rini_save_config(config, DisplayText::CONFIG_FILE_NAME.c_str());
}
void SettingManager::Init()
{
    config = rini_load_config(DisplayText::CONFIG_FILE_NAME.c_str());

    UpdateWindow();
    UpdateMaxFPS();
}

void SettingManager::Update()
{
}

void SettingManager::Unload()
{
}

void SettingManager::SetTheme(Theme theme)
{
    rini_set_config_value(&config, DisplayText::THEME.c_str(), static_cast<int>(theme), NULL);
    SaveConfig();
}

Theme SettingManager::GetTheme()
{
    int theme = rini_get_config_value(config, DisplayText::THEME.c_str());
    if (theme == 0)
        return DefaultSetting::DEFAULT_THEME;
    return static_cast<Theme>(theme);
}

Color SettingManager::GetColor(ColorPallet colorPallet)
{
    if (SettingManager::GetTheme() == Theme::Light)
    {
        switch (colorPallet)
        {
        case ColorPallet::Main:
            return GameColor::LIGHT_MAIN;
        case ColorPallet::Sub:
            return GameColor::LIGHT_SUB;
        case ColorPallet::Glay:
            return GameColor::LIGHT_GRAY;
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

    if (SettingManager::GetTheme() == Theme::Dark)
    {
        switch (colorPallet)
        {
        case ColorPallet::Main:
            return GameColor::DARK_MAIN;
        case ColorPallet::Sub:
            return GameColor::DARK_SUB;
        case ColorPallet::Glay:
            return GameColor::DARK_GRAY;
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

WindowMode SettingManager::GetWindowMode()
{
    int windowMode = rini_get_config_value(config, DisplayText::WINDOW_MODE.c_str());
    if (windowMode == 0)
        return DefaultSetting::DEFAULT_WINDOW_MODE;
    return static_cast<WindowMode>(windowMode);
}

void SettingManager::SetWindowMode(WindowMode windowMode)
{
    rini_set_config_value(&config, DisplayText::WINDOW_MODE.c_str(), static_cast<int>(windowMode), NULL);
    SaveConfig();

    UpdateWindow();
}

int SettingManager::GetMonitorID()
{
    int monitorID = rini_get_config_value(config, DisplayText::MONITOR_ID.c_str());
    if (monitorID == 0)
        return DefaultSetting::DEFAULT_MONITOR_ID;
    return monitorID;
}

void SettingManager::SetMonitorID(int monitorID)
{
    rini_set_config_value(&config, DisplayText::MONITOR_ID.c_str(), monitorID, NULL);
    SaveConfig();

    UpdateWindow();
}

int SettingManager::GetMaxFPS()
{
    int targetFPS = rini_get_config_value(config, DisplayText::MAX_FPS.c_str());
    if (targetFPS == 0)
        return DefaultSetting::DEFAULT_MAX_FPS;
    return targetFPS;
}

void SettingManager::SetMaxFPS(int targetFPS)
{
    rini_set_config_value(&config, DisplayText::MAX_FPS.c_str(), targetFPS, NULL);
    SaveConfig();

    UpdateMaxFPS();
}

void SettingManager::UpdateWindow()
{
    int monitorID = SettingManager::GetMonitorID() - 1;
    Vector2 monitorPosition = GetMonitorPosition(monitorID);
    int monitorWidth = GetMonitorWidth(monitorID);
    int monitorHeight = GetMonitorHeight(monitorID);

    switch (SettingManager::GetWindowMode())
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

void SettingManager::UpdateMaxFPS()
{
    SetTargetFPS(SettingManager::GetMaxFPS());
}