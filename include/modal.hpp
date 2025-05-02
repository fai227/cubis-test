#pragma once

#include "ui.hpp"
#include <string>
#include <list>
#include <functional>
#include "raylib.h"

class Modal
{
public:
    Modal(std::string message, std::string buttonText, std::function<void()> buttonCallback);
    Modal(std::string message, std::string leftButtonText, std::string rightButtonText, std::function<void()> leftButtonCallback, std::function<void()> rightButtonCallback);
    void Draw(Vector2 size);

    Text *messageText;
    Button *leftButton;
    Button *rightButton;
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