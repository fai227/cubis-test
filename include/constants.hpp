#pragma once

#include <string>
#include "setting.hpp"
#include "raylib.h"

namespace DisplayText
{
    const std::string GAME_TITLE = "Cubis ver0.1.0";

    const std::string CONFIG_FILE_NAME = "config.ini";

    const std::string THEME = "Theme";
    const std::string WINDOW_MODE = "WindowMode";
    const std::string MONITOR_ID = "MonitorID";
    const std::string MAX_FPS = "MaxFPS";
}

namespace DefaultSetting
{
    const Theme DEFAULT_THEME = Theme::Light;
    const WindowMode DEFAULT_WINDOW_MODE = WindowMode::Windowed;
    const int DEFAULT_MONITOR_ID = 1;
    const Vector2 DEFAULT_WINDOW_SIZE = {1280, 720};
    const int DEFAULT_MAX_FPS = 60;
}

namespace GameColor
{
    const Color LIGHT_MAIN = {10, 10, 10, 255};
    const Color DARK_MAIN = {245, 245, 245, 255};

    const Color LIGHT_SUB = {245, 245, 245, 255};
    const Color DARK_SUB = {10, 10, 10, 255};

    const Color LIGHT_GREEN = GREEN;
    const Color DARK_GREEN = GREEN;

    const Color LIGHT_RED = RED;
    const Color DARK_RED = RED;

    const Color LIGHT_BLUE = BLUE;
    const Color DARK_BLUE = BLUE;

    const Color LIGHT_ORANGE = ORANGE;
    const Color DARK_ORANGE = ORANGE;

    const Color LIGHT_PURPLE = PURPLE;
    const Color DARK_PURPLE = PURPLE;

    const Color LIGHT_YELLOW = YELLOW;
    const Color DARK_YELLOW = YELLOW;

    const Color LIGHT_CYAN = SKYBLUE;
    const Color DARK_CYAN = SKYBLUE;
}