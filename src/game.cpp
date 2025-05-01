#define RINI_IMPLEMENTATION
// #define RRES_RAYLIB_IMPLEMENTATION
// #define RRES_IMPLEMENTATION

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

    InputManager::Init();

    AudioManager::Init();
    RenderManager::Init();
}

void Game::Mainloop()
{
    while (!WindowShouldClose())
    {
        SystemManager::Update();
        SettingManager::Update();

        InputManager::Update();

        AudioManager::Update();
        RenderManager::Update();
    }
}

void Game::Unload()
{
    SystemManager::Unload();
    SettingManager::Unload();

    InputManager::Unload();

    AudioManager::Unload();
    RenderManager::Unload();
}

void Game::Run()
{
    Init();
    Mainloop();
    Unload();
}
