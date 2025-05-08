#include "debug.hpp"
#include "raylib.h"
#include "setting.hpp"
#include "constants.hpp"
#include "input.hpp"
#include "player.hpp"

void DebugManager::Init()
{
}

void DebugManager::Update()
{
    // FPS
    DrawFPS(10, 10);

    // Player Count
    int playerCount = PlayerManager::GetPlayerCount();
    std::string playerCountText = "Player Count: " + std::to_string(playerCount);
    DrawText(playerCountText.c_str(), 10, 30, 20, WHITE);
}

void DebugManager::Unload()
{
}