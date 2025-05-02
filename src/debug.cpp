#include "debug.hpp"
#include "raylib.h"
#include "setting.hpp"
#include "constants.hpp"
#include "input.hpp"

void DebugManager::Init()
{
}

void DebugManager::Update()
{
    // FPS
    DrawFPS(10, 10);
}

void DebugManager::Unload()
{
}