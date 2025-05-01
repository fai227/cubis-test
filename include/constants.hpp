#pragma once

#include <string>
#include "setting.hpp"
#include "raylib.h"

namespace DisplayText
{
    const std::string CONFIG_FILE_NAME = "config.ini";

    const std::string THEME = "Theme";
    const std::string THEME_DESCRIPTION = "Theme of the Game (1: Light, 2: Dark)";
    const std::string WINDOW_MODE = "WindowMode";
    const std::string WINDOW_MODE_DESCRIPTION = "Window Mode. (1: Windowed, 2: Borderless)";
    const std::string MONITOR_ID = "MonitorID";
    const std::string MONITOR_ID_DESCRIPTION = "Monitor ID. for multi-monitor setup.";
    const std::string MAX_FPS = "MaxFPS";
    const std::string MAX_FPS_DESCRIPTION = "Max Framerate.";

    const std::string GAME_TITLE = "Cubis";
    const std::string GAME_TITLE_WITH_VERSION = "Cubis [Ver 0.1.0]";
    const std::string START_BUTTON_TEXT = "Press [Return] / [A] to Start";

    const std::string SWITCH_THEME_BUTTON_TEXT = "Switch Theme";

    const std::string SOLO_BUTTON_TEXT = "Solo";
    const std::string LOCAL_BUTTON_TEXT = "Local";
    const std::string ONLINE_BUTTON_TEXT = "Online";
    const std::string FORTY_LINES_BUTTON_TEXT = "40 Lines";
    const std::string SCORE_ATTACK_BUTTON_TEXT = "Score Attack";
    const std::string VS_MODE_BUTTON_TEXT = "VS Mode";
    const std::string RANKED_MATCH_BUTTON_TEXT = "Ranked Match";
    const std::string CUSTOM_MATCH_BUTTON_TEXT = "Custom Match";
    const std::string PLAYER_JOIN_TEXT = "Press [Space] / [+] to Join";
    const std::string PLAYER_QUIT_TEXT = "Press [Escape] / [-] to Quit";
}

namespace DefaultSetting
{
    const Theme DEFAULT_THEME = Theme::Light;
    const WindowMode DEFAULT_WINDOW_MODE = WindowMode::Windowed;
    const int DEFAULT_MONITOR_ID = 1;
    const Vector2 DEFAULT_WINDOW_SIZE = {1280, 720};
    const int DEFAULT_MAX_FPS = 60;
}

namespace Constants
{
    const int MANIMUM_WINDOW_WIDTH = 640;
    const int MANIMUM_WINDOW_HEIGHT = 360;

    const float ASPECT_RATIO = 16.0f / 9.0f;

    const float MAX_TEXT_SIZE_IN_BOUNDS = 0.75f;

    const float TRANSITION_DURATION = 1.0f;
}

namespace GameColor
{
    const Color LIGHT_MAIN = {10, 10, 10, 255};
    const Color DARK_MAIN = {245, 245, 245, 255};

    const Color LIGHT_SUB = {245, 245, 245, 255};
    const Color DARK_SUB = {10, 10, 10, 255};

    const Color LIGHT_GRAY = {128, 128, 128, 255};
    const Color DARK_GRAY = {128, 128, 128, 255};

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