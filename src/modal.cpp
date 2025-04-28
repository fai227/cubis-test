#include "modal.hpp"
#include <list>

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
}

void ModalManager::PushModal(Modal *modal)
{
    modals.push_front(modal);
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