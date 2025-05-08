#define RINI_IMPLEMENTATION

#include "raylib.h"
#include "game.hpp"
#include "system.hpp"
#include "setting.hpp"
#include "audio.hpp"
#include "input.hpp"
#include "player.hpp"
#include "render.hpp"

bool Game::shouldExit = false;

void Game::Init()
{
    SystemManager::Init();
    SettingManager::Init();

    InputManager::Init();
    PlayerManager::Init();

    AudioManager::Init();
    RenderManager::Init();
}

void Game::Mainloop()
{
    while (!WindowShouldClose() && !shouldExit)
    {
        SystemManager::Update();
        SettingManager::Update();

        InputManager::Update();
        PlayerManager::Update();

        AudioManager::Update();
        RenderManager::Update();
    }
}

void Game::Unload()
{
    SystemManager::Unload();
    SettingManager::Unload();

    InputManager::Unload();
    PlayerManager::Unload();

    AudioManager::Unload();
    RenderManager::Unload();
}

void Game::Run()
{
    Init();
    Mainloop();
    Unload();
}

void Game::RequestExit()
{
    shouldExit = true;
}