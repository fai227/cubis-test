#include "scene.hpp"
#include "input.hpp"
#include "modal.hpp"

void SceneManager::Update(Rectangle target)
{
    InputManager::Update();

    if (isTransitioning)
    {
        nextScene->Update();
    }

    currentScene->Update();

    if (ModalManager::ModalExists())
    {
        Modal *modal = ModalManager::GetFirstModal();
        modal->Draw();
    }
}