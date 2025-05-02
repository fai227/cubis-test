#pragma once

#include <string>
#include "setting.hpp"
#include "raylib.h"

namespace ConfigFileText
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
    const std::string GENERAL_SENSITIVITY = "GeneralSensitivity";
    const std::string GENERAL_SENSITIVITY_DESCRIPTION = "General Sensitivity for Mouse Cursor.";
    const std::string GENERAL_THRESHOLD = "GeneralThreshold";
    const std::string GENERAL_THRESHOLD_DESCRIPTION = "General Threshold for Gamepad Joysticks and Triggers.";
}

namespace GameTitleText
{
    const std::string GAME_TITLE = "Cubis v0.2.0";
}

namespace UIElementDisplayText
{
    const std::string CUBIS = "Cubis";
    const std::string PRESS_RETURN_OR_A_TO_START = "Press [Return] / [A] to Start";
    const std::string LOCAL = "Local";
    const std::string ONLINE = "Online";
    const std::string EXIT_GAME = "Exit Game";
    const std::string THEME = "Theme";
    const std::string SETTING = "Setting";
    const std::string LEADERBOARD = "Leaderboard";
    const std::string BATTLE_MODE = "Battle Mode:";
    const std::string NO_TEXT_1 = ">";
    const std::string CHANGABLE_TEXT = "#";
    const std::string NO_TEXT_2 = "<";
    const std::string PLAYER_COUNT = "Player Count:";
    const std::string START_GAME = "Start Game";
    const std::string PRESS_RETURN_OR_PLUS_TO_JOIN_QUIT = "Press [Return] / [+] to Join (Quit)";
    const std::string BACK_TO_MENU = "Back to Menu";
    const std::string MOVE_MINO_FORWARD = "Move Mino Forward";
    const std::string MOVE_MINO_BACKWARD = "Move Mino Backward";
    const std::string MOVE_MINO_RIGHT = "Move Mino Right";
    const std::string MOVE_MINO_LEFT = "Move Mino Left";
    const std::string MOVE_CAMERA_RIGHT = "Move Camera Right";
    const std::string MOVE_MINO_DOWN = "Move Mino Down";
    const std::string HOLD_MINO = "Hold Mino";
    const std::string ROTATE_MINO_YPLUS = "Rotate Mino Y+";
    const std::string ROTATE_MINO_YMINUS = "Rotate Mino Y-";
    const std::string ROTATE_MINO_XPLUS = "Rotate Mino X+";
    const std::string ROTATE_MINO_XMINUS = "Rotate Mino X-";
    const std::string ROTATE_MINO_ZPLUS = "Rotate Mino Z+";
    const std::string ROTATE_MINO_ZMINUS = "Rotate Mino Z-";
    const std::string DROP_MINO = "Drop Mino";
    const std::string MOVE_CAMERA_LEFT = "Move Camera Left";
    const std::string MOVE_CAMERA_UP = "Move Camera Up";
    const std::string MOVE_CAMERA_DOWN = "Move Camera Down";
    const std::string MOUSE_CURSOR_DOWN = "Mouse Cursor Down";
    const std::string MOUSE_CURSOR_UP = "Mouse Cursor Up";
    const std::string MOUSE_CURSOR_LEFT = "Mouse Cursor Left";
    const std::string MOUSE_CURSOR_RIGHT = "Mouse Cursor Right";
    const std::string LEFT_SHIFT = "Left Shift";
    const std::string SPACE = "Space";
    const std::string LEFT_CLICK = "Left Click";
    const std::string E = "E";
    const std::string MOUSE_WHEEL_DOWN = "Mouse Wheel Down";
    const std::string LEFT_CTRL = "Left Ctrl";
    const std::string W = "W";
    const std::string A = "A";
    const std::string RIGHT_CLICK = "Right Click";
    const std::string Q = "Q";
    const std::string MOUSE_WHEEL_UP = "Mouse Wheel Up";
    const std::string S = "S";
    const std::string D = "D";
    const std::string RIGHT_JOYSTICK_DOWN = "Right Joystick Down";
    const std::string RIGHT_JOYSTICK_UP = "Right Joystick Up";
    const std::string RIGHT_JOYSTICK_LEFT = "Right Joystick Left";
    const std::string RIGHT_JOYSTICK_RIGHT = "Right Joystick Right";
    const std::string LEFT_TRIGGER = "Left Trigger";
    const std::string RIGHT_TRIGGER = "Right Trigger";
    const std::string BUTTON_DOWN = "Button Down";
    const std::string RIGHT_SHOULDER = "Right Shoulder";
    const std::string DMINUSPAD_DOWN = "D-Pad Down";
    const std::string LEFT_JOYSTICK_UP = "Left Joystick Up";
    const std::string LEFT_JOYSTICK_LEFT = "Left Joystick Left";
    const std::string BUTTON_RIGHT = "Button Right";
    const std::string LEFT_SHOULDER = "Left Shoulder";
    const std::string BUTTON_UP = "Button Up";
    const std::string LEFT_JOYSTICK_DOWN = "Left Joystick Down";
    const std::string LEFT_JOYSTICK_RIGHT = "Left Joystick Right";
    const std::string CONTROL = "Control";
    const std::string GENERAL = "General";
    const std::string WINDOW_MODE = "Window Mode";
    const std::string MONITOR = "Monitor";
    const std::string MAX_FRAMERATE = "Max Framerate";
    const std::string MOUSE_SENSITIVITY = "Mouse Sensitivity";
    const std::string CONTROLLER_THRESHOLD = "Controller Threshold";
}

namespace DefaultSetting
{
    const Theme DEFAULT_THEME = Theme::Light;
    const WindowMode DEFAULT_WINDOW_MODE = WindowMode::Windowed;
    const int DEFAULT_MONITOR_ID = 1;
    const Vector2 DEFAULT_WINDOW_SIZE = {1280, 720};
    const int DEFAULT_MAX_FPS = 60'000;
    const int DEFAULT_GENERAL_SENSITIVITY = 10;
    const int DEFAULT_GENERAL_THRESHOLD = 5;
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