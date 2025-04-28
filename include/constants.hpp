#pragma once

#include "setting.hpp"
#include "raylib.h"

namespace DisplayText
{
    constexpr const char *GAME_TITLE = "Cubis ver0.1.0";

    constexpr const char *CONFIG_FILE_NAME = "config.ini";

    constexpr const char *THEME = "Theme";
    constexpr const char *WINDOW_MODE = "WindowMode";
    constexpr const char *MONITOR_ID = "MonitorID";
    constexpr const char *MAX_FPS = "MaxFPS";
}

namespace DefaultSetting
{
    constexpr const Theme DEFAULT_THEME = Theme::Light;
    constexpr const WindowMode DEFAULT_WINDOW_MODE = WindowMode::Windowed;
    constexpr const int DEFAULT_MONITOR_ID = 1;
    constexpr const Vector2 DEFAULT_WINDOW_SIZE = {1280, 720};
    constexpr const int DEFAULT_MAX_FPS = 60;
}

namespace GameColor
{
    constexpr const Color LIGHT_MAIN = {245, 245, 245, 255};
    constexpr const Color DARK_MAIN = {10, 10, 10, 255};

    constexpr const Color LIGHT_SUB = {10, 10, 10, 255};
    constexpr const Color DARK_SUB = {245, 245, 245, 255};

    constexpr const Color LIGHT_GREEN = GREEN;
    constexpr const Color DARK_GREEN = GREEN;

    constexpr const Color LIGHT_RED = RED;
    constexpr const Color DARK_RED = RED;

    constexpr const Color LIGHT_BLUE = BLUE;
    constexpr const Color DARK_BLUE = BLUE;

    constexpr const Color LIGHT_ORANGE = ORANGE;
    constexpr const Color DARK_ORANGE = ORANGE;

    constexpr const Color LIGHT_PURPLE = PURPLE;
    constexpr const Color DARK_PURPLE = PURPLE;

    constexpr const Color LIGHT_YELLOW = YELLOW;
    constexpr const Color DARK_YELLOW = YELLOW;

    constexpr const Color LIGHT_CYAN = SKYBLUE;
    constexpr const Color DARK_CYAN = SKYBLUE;
}