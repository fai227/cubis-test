#include "modal.hpp"

#include <list>
#include "input.hpp"
#include "raylib.h"
#include "setting.hpp"

Modal::Modal(std::string message, std::string buttonText, std::function<void()> buttonCallback)
{
    messageText = new Text({0.500, 0.438, 0.500, 0.058}, message.c_str());
    leftButton = new Button({0.5, 0.540, 0.221, 0.076}, buttonText.c_str());
}

Modal::Modal(std::string message, std::string leftButtonText, std::string rightButtonText, std::function<void()> leftButtonCallback, std::function<void()> rightButtonCallback)
{
    messageText = new Text({0.500, 0.438, 0.500, 0.058}, message.c_str());
    leftButton = new Button({0.381, 0.540, 0.221, 0.076}, leftButtonText.c_str());
    rightButton = new Button({0.619, 0.540, 0.221, 0.076}, rightButtonText.c_str());

    leftButton->SetNavigation(nullptr, nullptr, nullptr, rightButton);
    rightButton->SetNavigation(nullptr, nullptr, leftButton, nullptr);

    leftButton->OnClick = leftButtonCallback;
    rightButton->OnClick = rightButtonCallback;
}

void Modal::Draw(Vector2 size)
{
    Rectangle modalBounds = UI::GetScreenBounds(size, {0.5f, 0.5f, 0.5f, 0.247f});

    DrawRectangleRec(modalBounds, SettingManager::GetColor(ColorPallet::Sub));
    DrawRectangleLines(modalBounds.x, modalBounds.y, modalBounds.width, modalBounds.height, SettingManager::GetColor(ColorPallet::Main));

    messageText->Draw(size);

    leftButton->Draw(size);
    if (rightButton != nullptr)
    {
        rightButton->Draw(size);
    }
}

std::list<Modal *> ModalManager::modals;

bool ModalManager::ModalExists()
{
    return !modals.empty();
}

void ModalManager::EnqueueModal(Modal *modal)
{
    modals.push_back(modal);

    // Set Navigation if this is the first modal
    if (ModalManager::GetFirstModal() == modal)
    {
        InputManager::SetNavigationEnabled(true);
        InputManager::SetSelectedItem(modal->leftButton);
    }
}

void ModalManager::PushModal(Modal *modal)
{
    modals.push_front(modal);

    // Set Navigation
    InputManager::SetNavigationEnabled(true);
    InputManager::SetSelectedItem(modal->leftButton);
}

void ModalManager::DequeModal()
{
    if (!modals.empty())
    {
        delete modals.front();
        modals.pop_front();
    }
}

Modal *ModalManager::GetFirstModal()
{
    if (!modals.empty())
    {
        return modals.front();
    }
    return nullptr;
}