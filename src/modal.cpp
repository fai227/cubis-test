#include "modal.hpp"

#include <list>
#include "input.hpp"

Modal::Modal(std::string message, std::string leftButtonText, std::string rightButtonText, std::function<void()> leftButtonCallback, std::function<void()> rightButtonCallback, bool defaultLeftSelected)
{
    this->message = message;
    this->leftButtonText = leftButtonText;
    this->rightButtonText = rightButtonText;
    this->leftButtonCallback = leftButtonCallback;
    this->rightButtonCallback = rightButtonCallback;
    this->defaultLeftSelected = defaultLeftSelected;

    messageText = new Text({0.500, 0.414, 0.476, 0.386}, message.c_str());
    leftButton = new Button({0.500, 0.685, 0.396, 0.076}, leftButtonText.c_str());
    rightButton = new Button({0.500, 0.685 + 0.396 + 0.025, 0.396, 0.076}, rightButtonText.c_str());

    leftButton->SetNavigation(nullptr, nullptr, nullptr, rightButton);
    rightButton->SetNavigation(nullptr, nullptr, leftButton, nullptr);
}

void Modal::Draw()
{
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
        InputManager::SetSelectedItem(modal->defaultLeftSelected ? modal->leftButton : modal->rightButton);
    }
}

void ModalManager::PushModal(Modal *modal)
{
    modals.push_front(modal);

    // Set Navigation
    InputManager::SetNavigationEnabled(true);
    InputManager::SetSelectedItem(modal->defaultLeftSelected ? modal->leftButton : modal->rightButton);
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