#include "setting.hpp"
#include "rini.h"
#include "constants.hpp"

rini_config SettingManager::config;

void SettingManager::SaveConfig()
{
    rini_save_config(config, ConfigFileText::CONFIG_FILE_NAME.c_str());
}
void SettingManager::Init()
{
    config = rini_load_config(ConfigFileText::CONFIG_FILE_NAME.c_str());

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
    rini_set_config_value(&config, ConfigFileText::THEME.c_str(), static_cast<int>(theme), ConfigFileText::THEME_DESCRIPTION.c_str());
    SaveConfig();
}

Theme SettingManager::GetTheme()
{
    int theme = rini_get_config_value(config, ConfigFileText::THEME.c_str());

    if (theme < 0 || theme >= static_cast<int>(Theme::Count))
    {
        TraceLog(LOG_WARNING, "SettingManager::GetTheme: Invalid theme: %d", theme);
        return DefaultSetting::DEFAULT_THEME;
    }

    if (theme == 0)
    {
        return DefaultSetting::DEFAULT_THEME;
    }

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

    TraceLog(LOG_WARNING, "SettingManager::GetColor: Invalid colorPallet: %d", static_cast<int>(colorPallet));
    return BLANK;
}

WindowMode SettingManager::GetWindowMode()
{
    int windowMode = rini_get_config_value(config, ConfigFileText::WINDOW_MODE.c_str());

    if (windowMode < 0 || windowMode >= static_cast<int>(WindowMode::Count))
    {
        TraceLog(LOG_WARNING, "SettingManager::GetWindowMode: Invalid windowMode: %d", windowMode);
        return DefaultSetting::DEFAULT_WINDOW_MODE;
    }

    if (windowMode == 0)
    {
        return DefaultSetting::DEFAULT_WINDOW_MODE;
    }

    return static_cast<WindowMode>(windowMode);
}

WindowMode SettingManager::GetNextWindowMode(bool isNext)
{
    WindowMode windowMode = SettingManager::GetWindowMode();
    if (windowMode == WindowMode::Windowed)
    {
        return WindowMode::Borderless;
    }
    return WindowMode::Windowed;
}

void SettingManager::SetWindowMode(WindowMode windowMode)
{
    rini_set_config_value(&config, ConfigFileText::WINDOW_MODE.c_str(), static_cast<int>(windowMode), ConfigFileText::WINDOW_MODE_DESCRIPTION.c_str());
    SaveConfig();

    UpdateWindow();
}

int SettingManager::GetMonitorID()
{
    int monitorID = rini_get_config_value(config, ConfigFileText::MONITOR_ID.c_str());

    if (monitorID < 0 || monitorID > GetMonitorCount())
    {
        TraceLog(LOG_WARNING, "SettingManager::GetMonitorID: Invalid monitorID: %d", monitorID);
        return DefaultSetting::DEFAULT_MONITOR_ID;
    }

    if (monitorID == 0)
    {
        return DefaultSetting::DEFAULT_MONITOR_ID;
    }

    return monitorID;
}

int SettingManager::GetNextMonitorID(bool isNext)
{
    int monitorID = SettingManager::GetMonitorID();
    if (isNext)
    {
        return (monitorID % GetMonitorCount()) + 1;
    }
    return (monitorID - 2 + GetMonitorCount()) % GetMonitorCount() + 1;
}

void SettingManager::SetMonitorID(int monitorID)
{
    rini_set_config_value(&config, ConfigFileText::MONITOR_ID.c_str(), monitorID, ConfigFileText::MONITOR_ID_DESCRIPTION.c_str());
    SaveConfig();

    UpdateWindow();
}

int SettingManager::GetMaxFPS()
{
    int targetFPS = rini_get_config_value(config, ConfigFileText::MAX_FPS.c_str());

    if (targetFPS < 0)
    {
        TraceLog(LOG_WARNING, "SettingManager::GetMaxFPS: Invalid targetFPS: %d", targetFPS);
        return DefaultSetting::DEFAULT_MAX_FPS;
    }

    if (targetFPS == 0)
    {
        return DefaultSetting::DEFAULT_MAX_FPS;
    }

    return targetFPS;
}

int SettingManager::GetNextMaxFPS(bool isNext)
{
    // 30 50 60 75 120 144 165 240 360 480
    int targetFPS = SettingManager::GetMaxFPS();
    if (isNext)
    {
        switch (targetFPS)
        {
        case 30:
            return 50;
        case 50:
            return 60;
        case 60:
            return 75;
        case 75:
            return 120;
        case 120:
            return 144;
        case 144:
            return 165;
        case 165:
            return 240;
        case 240:
            return 360;
        case 360:
            return 480;
        case 480:
            return 30;
        }
    }
    else
    {
        switch (targetFPS)
        {
        case 30:
            return 480;
        case 50:
            return 30;
        case 60:
            return 50;
        case 75:
            return 60;
        case 120:
            return 75;
        case 144:
            return 120;
        case 165:
            return 144;
        case 240:
            return 165;
        case 360:
            return 240;
        case 480:
            return 360;
        }
    }

    TraceLog(LOG_WARNING, "SettingManager::GetNextMaxFPS: Invalid targetFPS: %d", targetFPS);
    return DefaultSetting::DEFAULT_MAX_FPS;
}

void SettingManager::SetMaxFPS(int targetFPS)
{
    rini_set_config_value(&config, ConfigFileText::MAX_FPS.c_str(), targetFPS, ConfigFileText::MAX_FPS_DESCRIPTION.c_str());
    SaveConfig();

    UpdateMaxFPS();
}

int SettingManager::GetGeneralSensitivity()
{
    int sensitivity = rini_get_config_value(config, ConfigFileText::GENERAL_SENSITIVITY.c_str());

    if (sensitivity < 0 || sensitivity > 20)
    {
        TraceLog(LOG_WARNING, "SettingManager::GetGeneralSensitivity: Invalid sensitivity: %d", sensitivity);
        return DefaultSetting::DEFAULT_GENERAL_SENSITIVITY;
    }

    if (sensitivity == 0)
    {
        return DefaultSetting::DEFAULT_GENERAL_SENSITIVITY;
    }

    return sensitivity;
}

int SettingManager::GetNextGeneralSensitivity(bool isNext)
{
    int sensitivity = SettingManager::GetGeneralSensitivity();
    if (isNext)
    {
        return (sensitivity % 20) + 1;
    }
    return (sensitivity - 2 + 20) % 20 + 1;
}

void SettingManager::SetGeneralSensitivity(int sensitivity)
{
    rini_set_config_value(&config, ConfigFileText::GENERAL_SENSITIVITY.c_str(), sensitivity, ConfigFileText::GENERAL_SENSITIVITY_DESCRIPTION.c_str());
    SaveConfig();
}

float SettingManager::GetGeneralSensitivityFloat()
{
    int sensitivity = SettingManager::GetGeneralSensitivity();

    // (int)1~10 -> (float)0.1~1.0
    if (sensitivity <= 10)
    {
        return static_cast<float>(sensitivity) / 10.0f;
    }

    // (int)11~20 -> (flaot)1~100
    return (static_cast<float>(sensitivity) - 10.0f) * 10.0f;
}

int SettingManager::GetGeneralThreshold()
{
    int threshold = rini_get_config_value(config, ConfigFileText::GENERAL_THRESHOLD.c_str());

    if (threshold < 0 || threshold > 10)
    {
        TraceLog(LOG_WARNING, "SettingManager::GetGeneralThreshold: Invalid threshold: %d", threshold);
        return DefaultSetting::DEFAULT_GENERAL_THRESHOLD;
    }

    if (threshold == 0)
    {
        return DefaultSetting::DEFAULT_GENERAL_THRESHOLD;
    }

    return threshold;
}

void SettingManager::SetGeneralThreshold(int threshold)
{
    rini_set_config_value(&config, ConfigFileText::GENERAL_THRESHOLD.c_str(), threshold, ConfigFileText::GENERAL_THRESHOLD_DESCRIPTION.c_str());
    SaveConfig();
}

int SettingManager::GetNextGeneralThreshold(bool isNext)
{
    int threshold = SettingManager::GetGeneralThreshold();
    if (isNext)
    {
        return (threshold % 10) + 1;
    }
    return (threshold - 2 + 10) % 10 + 1;
}

float SettingManager::GetGeneralThresholdFloat()
{
    int threshold = SettingManager::GetGeneralThreshold();

    // (int)1~10 -> (float)0.0~0.9
    return static_cast<float>(threshold) / 10.0f - 0.1f;
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

std::string SettingManager::ConvertWindowModeToString(WindowMode windowMode)
{
    switch (windowMode)
    {
    case WindowMode::Windowed:
        return GameText::WINDOWED.c_str();
    case WindowMode::Borderless:
        return GameText::BORDERLESS.c_str();
    }

    TraceLog(LOG_WARNING, "SettingManager::ConvertWindowModeToString: Invalid windowMode: %d", static_cast<int>(windowMode));
    return SettingManager::ConvertWindowModeToString(DefaultSetting::DEFAULT_WINDOW_MODE);
}

std::string SettingManager::ConvertMonitorIDToString(int monitorID)
{
    return std::to_string(monitorID);
}

std::string SettingManager::ConvertMaxFPSToString(int maxFPS)
{
    return std::to_string(maxFPS);
}

std::string SettingManager::ConvertGeneralSensitivityToString(int sensitivity)
{
    return std::to_string(sensitivity);
}

std::string SettingManager::ConvertGeneralThresholdToString(int threshold)
{
    return std::to_string(threshold);
}

ColorPallet SettingManager::GetPlayerColor(int playerID)
{
    switch (playerID)
    {
    case 1:
        return ColorPallet::Red;
    case 2:
        return ColorPallet::Green;
    case 3:
        return ColorPallet::Yellow;
    case 4:
        return ColorPallet::Cyan;
    }

    TraceLog(LOG_WARNING, "SettingManager::GetPlayerColor: Invalid playerID: %d", playerID);
    return ColorPallet::Sub;
}