#pragma once

#include <string>
#include <list>
#include <functional>

class Modal
{
private:
    std::string message;
    std::string leftButtonText;
    std::string rightButtonText;
    std::function<void()> leftButtonCallback;
    std::function<void()> rightButtonCallback;
    bool defaultLeftSelected;

public:
    Modal(std::string, std::string, std::string, std::function<void()>, std::function<void()>, bool);
    void Draw();
};

class ModalManager
{
private:
    static std::list<Modal *> modals;

public:
    static bool ModalExists();

    static void EnqueueModal(Modal *modal);
    static void PushModal(Modal *modal);

    static void DequeModal();
    static Modal *GetFirstModal();
};