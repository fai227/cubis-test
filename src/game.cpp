#define RINI_IMPLEMENTATION

#include "raylib.h"
#include "game.hpp"
#include "system.hpp"
#include "setting.hpp"
#include "audio.hpp"
#include "input.hpp"
#include "render.hpp"

void Game::Init()
{
    SystemManager::Init();
    SettingManager::Init();

    AudioManager::Init();
    InputManager::Init();

    RenderManager::Init();
}

void Game::Mainloop()
{
    while (!WindowShouldClose())
    {
        SystemManager::Update();
        SettingManager::Update();

        AudioManager::Update();
        InputManager::Update();

        RenderManager::Update();
    }
}

void Game::Unload()
{
    SystemManager::Unload();
    SettingManager::Unload();

    AudioManager::Unload();
    InputManager::Unload();

    RenderManager::Unload();
}

void Game::Run()
{
    Init();
    Mainloop();
    Unload();
}
