#include "scene.hpp"
#include "ui.hpp"
#include <vector>
#include "setting.hpp"
#include "raylib.h"
#include "constants.hpp"
#include "render.hpp"
#include "input.hpp"
#include "game.hpp"
#include "modal.hpp"
#include "rule.hpp"

Scene::Scene()
{
    TraceLog(LOG_INFO, "Scene created.");
}

void Scene::Update(Vector2 size)
{
    ClearBackground(SettingManager::GetColor(ColorPallet::Sub));
    for (UIElement *element : uiElements)
    {
        element->Draw(size);
    }
}

Scene::~Scene()
{
    for (UIElement *element : uiElements)
    {
        delete element;
    }

    TraceLog(LOG_INFO, "Scene destroyed.");
}

BlankScene::BlankScene()
{
}

TitleScene::TitleScene()
{
    Text *text1 = new Text({0.500, 0.414, 0.476, 0.386}, UIElementDisplayText::CUBIS.c_str());
    Button *button1 = new Button({0.500, 0.685, 0.396, 0.076}, UIElementDisplayText::PRESS_RETURN_OR_A_TO_START.c_str());

    button1->SetNavigation(nullptr, nullptr, nullptr, nullptr);

    uiElements.push_back(text1);
    uiElements.push_back(button1);

    button1->OnClick = []()
    {
        InputManager::SetNavigationEnabled(false);
        InputManager::RemoveSelectedItem();
        RenderManager::TransitToNextScene(new MenuScene());
    };
}

void TitleScene::Enable()
{
    InputManager::SetNavigationEnabled(true);
    InputManager::SetSelectedItem(static_cast<Button *>(uiElements[1]));
}

MenuScene::MenuScene()
{
    Text *text1 = new Text({0.250, 0.189, 0.500, 0.272}, UIElementDisplayText::CUBIS.c_str());
    Button *button1 = new Button({0.248, 0.673, 0.176, 0.067}, UIElementDisplayText::EXIT_GAME.c_str());
    Button *button2 = new Button({0.248, 0.466, 0.176, 0.067}, UIElementDisplayText::THEME.c_str());
    Button *button3 = new Button({0.248, 0.569, 0.176, 0.067}, UIElementDisplayText::SETTING.c_str());
    Button *button4 = new Button({0.248, 0.363, 0.176, 0.067}, UIElementDisplayText::LEADERBOARD.c_str());
    Text *text2 = new Text({0.548, 0.371, 0.262, 0.076}, UIElementDisplayText::BATTLE_MODE.c_str());
    Button *button5 = new Button({0.899, 0.371, 0.038, 0.067}, UIElementDisplayText::NO_TEXT_1.c_str());
    Text *text3 = new Text({0.798, 0.371, 0.163, 0.058}, UIElementDisplayText::CHANGABLE_TEXT.c_str());
    Button *button6 = new Button({0.698, 0.371, 0.038, 0.067}, UIElementDisplayText::NO_TEXT_2.c_str());
    Text *text4 = new Text({0.548, 0.465, 0.262, 0.076}, UIElementDisplayText::PLAYER_COUNT.c_str());
    Button *button7 = new Button({0.899, 0.466, 0.038, 0.067}, UIElementDisplayText::NO_TEXT_1.c_str());
    Text *text5 = new Text({0.798, 0.466, 0.163, 0.058}, UIElementDisplayText::CHANGABLE_TEXT.c_str());
    Button *button8 = new Button({0.698, 0.466, 0.038, 0.067}, UIElementDisplayText::NO_TEXT_2.c_str());
    Button *button9 = new Button({0.698, 0.639, 0.319, 0.135}, UIElementDisplayText::START_GAME.c_str());
    Text *text6 = new Text({0.824, 0.820, 0.351, 0.058}, UIElementDisplayText::PRESS_RETURN_OR_PLUS_TO_JOIN_QUIT.c_str());

    button1->SetNavigation(button3, nullptr, nullptr, button9);
    button2->SetNavigation(button4, button3, nullptr, button8);
    button3->SetNavigation(button2, button1, nullptr, button9);
    button4->SetNavigation(nullptr, button2, nullptr, button6);
    button5->SetNavigation(nullptr, button7, button6, nullptr);
    button6->SetNavigation(nullptr, button8, button4, button5);
    button7->SetNavigation(button5, nullptr, button8, nullptr);
    button8->SetNavigation(button6, button9, button2, button7);
    button9->SetNavigation(button8, nullptr, button1, button7);

    uiElements.push_back(text1);
    uiElements.push_back(button1);
    uiElements.push_back(button2);
    uiElements.push_back(button3);
    uiElements.push_back(button4);
    uiElements.push_back(text2);
    uiElements.push_back(button5);
    uiElements.push_back(text3);
    uiElements.push_back(button6);
    uiElements.push_back(text4);
    uiElements.push_back(button7);
    uiElements.push_back(text5);
    uiElements.push_back(button8);
    uiElements.push_back(button9);
    uiElements.push_back(text6);

    button1->OnClick = [button1]()
    {
        Modal *modal = new Modal("Are you sure to exit game?", "No", "Yes", [button1]()
                                 {
            InputManager::SetNavigationEnabled(true);
            InputManager::SetSelectedItem(button1);
            ModalManager::DequeModal(); }, []()
                                 {
        InputManager::SetNavigationEnabled(false);
        Game::RequestExit(); });
        ModalManager::EnqueueModal(modal);
    };

    button2->OnClick = []()
    {
        Theme currentTheme = SettingManager::GetTheme();
        if (currentTheme == Theme::Light)
        {
            SettingManager::SetTheme(Theme::Dark);
        }
        else
        {
            SettingManager::SetTheme(Theme::Light);
        }
    };

    button3->OnClick = []()
    {
        InputManager::SetNavigationEnabled(false);
        InputManager::RemoveSelectedItem();
        RenderManager::TransitToNextScene(new OptionScene());
    };

    button4->OnClick = []()
    {
        InputManager::SetNavigationEnabled(false);
        InputManager::RemoveSelectedItem();
        RenderManager::TransitToNextScene(new LeaderboardScene());
    };

    button5->OnClick = [text3]()
    {
        GameMode nextGameMode = RuleManager::GetNextGameMode(true);
        RuleManager::SetGameMode(nextGameMode);
        text3->ChangeText(RuleManager::ConvertGameModeToString(nextGameMode));
    };
    text3->ChangeText(RuleManager::ConvertGameModeToString(RuleManager::GetGameMode()));
    button6->OnClick = [text3]()
    {
        GameMode nextGameMode = RuleManager::GetNextGameMode(false);
        RuleManager::SetGameMode(nextGameMode);
        text3->ChangeText(RuleManager::ConvertGameModeToString(nextGameMode));
    };

    button7->OnClick = [text5]()
    {
        int nextPlayerCount = RuleManager::GetNextPlayerCount(true);
        RuleManager::SetPlayerCount(nextPlayerCount);
        text5->ChangeText(RuleManager::ConvertPlayerCountToString(nextPlayerCount));
    };
    text5->ChangeText(std::to_string(RuleManager::GetPlayerCount()));
    button8->OnClick = [text5]()
    {
        int nextPlayerCount = RuleManager::GetNextPlayerCount(false);
        RuleManager::SetPlayerCount(nextPlayerCount);
        text5->ChangeText(RuleManager::ConvertPlayerCountToString(nextPlayerCount));
    };

    button9->OnClick = []()
    {
        InputManager::SetNavigationEnabled(false);
        InputManager::RemoveSelectedItem();
        RenderManager::TransitToNextScene(new GameScene());
    };
}

void MenuScene::Enable()
{
    InputManager::SetNavigationEnabled(true);
    InputManager::SetSelectedItem(static_cast<Button *>(uiElements[4]));
}

LeaderboardScene::LeaderboardScene()
{
    Text *text1 = new Text({0.500, 0.081, 1.000, 0.162}, UIElementDisplayText::LEADERBOARD.c_str());
    Button *button1 = new Button({0.166, 0.947, 0.290, 0.076}, UIElementDisplayText::BACK_TO_MENU.c_str());

    button1->SetNavigation(nullptr, nullptr, nullptr, nullptr);

    uiElements.push_back(text1);
    uiElements.push_back(button1);

    button1->OnClick = []()
    {
        InputManager::SetNavigationEnabled(false);
        InputManager::RemoveSelectedItem();
        RenderManager::TransitToNextScene(new MenuScene());
    };
}

void LeaderboardScene::Enable()
{
    InputManager::SetNavigationEnabled(true);
    InputManager::SetSelectedItem(static_cast<Button *>(uiElements[1]));
}

OptionScene::OptionScene()
{
    Button *button1 = new Button({0.166, 0.947, 0.290, 0.076}, UIElementDisplayText::BACK_TO_MENU.c_str());
    Text *text1 = new Text({0.165, 0.081, 0.330, 0.162}, UIElementDisplayText::SETTING.c_str());
    Text *text2 = new Text({0.448, 0.301, 0.201, 0.045}, UIElementDisplayText::MOVE_MINO_FORWARD.c_str());
    Text *text3 = new Text({0.448, 0.347, 0.201, 0.045}, UIElementDisplayText::MOVE_MINO_BACKWARD.c_str());
    Text *text4 = new Text({0.448, 0.210, 0.201, 0.045}, UIElementDisplayText::MOVE_MINO_RIGHT.c_str());
    Text *text5 = new Text({0.448, 0.255, 0.201, 0.045}, UIElementDisplayText::MOVE_MINO_LEFT.c_str());
    Text *text6 = new Text({0.448, 0.803, 0.201, 0.045}, UIElementDisplayText::MOVE_CAMERA_RIGHT.c_str());
    Text *text7 = new Text({0.448, 0.392, 0.201, 0.045}, UIElementDisplayText::MOVE_MINO_DOWN.c_str());
    Text *text8 = new Text({0.448, 0.757, 0.201, 0.045}, UIElementDisplayText::HOLD_MINO.c_str());
    Text *text9 = new Text({0.448, 0.529, 0.201, 0.045}, UIElementDisplayText::ROTATE_MINO_YPLUS.c_str());
    Text *text10 = new Text({0.448, 0.575, 0.201, 0.045}, UIElementDisplayText::ROTATE_MINO_YMINUS.c_str());
    Text *text11 = new Text({0.448, 0.438, 0.201, 0.045}, UIElementDisplayText::ROTATE_MINO_XPLUS.c_str());
    Text *text12 = new Text({0.448, 0.483, 0.201, 0.045}, UIElementDisplayText::ROTATE_MINO_XMINUS.c_str());
    Text *text13 = new Text({0.448, 0.620, 0.201, 0.045}, UIElementDisplayText::ROTATE_MINO_ZPLUS.c_str());
    Text *text14 = new Text({0.448, 0.666, 0.201, 0.045}, UIElementDisplayText::ROTATE_MINO_ZMINUS.c_str());
    Text *text15 = new Text({0.448, 0.711, 0.201, 0.045}, UIElementDisplayText::DROP_MINO.c_str());
    Text *text16 = new Text({0.448, 0.848, 0.201, 0.045}, UIElementDisplayText::MOVE_CAMERA_LEFT.c_str());
    Text *text17 = new Text({0.448, 0.894, 0.201, 0.045}, UIElementDisplayText::MOVE_CAMERA_UP.c_str());
    Text *text18 = new Text({0.448, 0.939, 0.201, 0.045}, UIElementDisplayText::MOVE_CAMERA_DOWN.c_str());
    Button *button2 = new Button({0.665, 0.939, 0.201, 0.038}, UIElementDisplayText::MOUSE_CURSOR_DOWN.c_str());
    Button *button3 = new Button({0.665, 0.894, 0.201, 0.038}, UIElementDisplayText::MOUSE_CURSOR_UP.c_str());
    Button *button4 = new Button({0.665, 0.848, 0.201, 0.038}, UIElementDisplayText::MOUSE_CURSOR_LEFT.c_str());
    Button *button5 = new Button({0.665, 0.803, 0.201, 0.038}, UIElementDisplayText::MOUSE_CURSOR_RIGHT.c_str());
    Button *button6 = new Button({0.665, 0.757, 0.201, 0.038}, UIElementDisplayText::LEFT_SHIFT.c_str());
    Button *button7 = new Button({0.665, 0.711, 0.201, 0.038}, UIElementDisplayText::SPACE.c_str());
    Button *button8 = new Button({0.665, 0.666, 0.201, 0.038}, UIElementDisplayText::LEFT_CLICK.c_str());
    Button *button9 = new Button({0.665, 0.574, 0.201, 0.038}, UIElementDisplayText::E.c_str());
    Button *button10 = new Button({0.665, 0.483, 0.201, 0.038}, UIElementDisplayText::MOUSE_WHEEL_DOWN.c_str());
    Button *button11 = new Button({0.665, 0.392, 0.201, 0.038}, UIElementDisplayText::LEFT_CTRL.c_str());
    Button *button12 = new Button({0.665, 0.301, 0.201, 0.038}, UIElementDisplayText::W.c_str());
    Button *button13 = new Button({0.665, 0.255, 0.201, 0.038}, UIElementDisplayText::A.c_str());
    Button *button14 = new Button({0.665, 0.620, 0.201, 0.038}, UIElementDisplayText::RIGHT_CLICK.c_str());
    Button *button15 = new Button({0.665, 0.529, 0.201, 0.038}, UIElementDisplayText::Q.c_str());
    Button *button16 = new Button({0.665, 0.438, 0.201, 0.038}, UIElementDisplayText::MOUSE_WHEEL_UP.c_str());
    Button *button17 = new Button({0.665, 0.346, 0.201, 0.038}, UIElementDisplayText::S.c_str());
    Button *button18 = new Button({0.665, 0.209, 0.201, 0.038}, UIElementDisplayText::D.c_str());
    Button *button19 = new Button({0.880, 0.939, 0.201, 0.038}, UIElementDisplayText::RIGHT_JOYSTICK_DOWN.c_str());
    Button *button20 = new Button({0.880, 0.894, 0.201, 0.038}, UIElementDisplayText::RIGHT_JOYSTICK_UP.c_str());
    Button *button21 = new Button({0.880, 0.848, 0.201, 0.038}, UIElementDisplayText::RIGHT_JOYSTICK_LEFT.c_str());
    Button *button22 = new Button({0.880, 0.803, 0.201, 0.038}, UIElementDisplayText::RIGHT_JOYSTICK_RIGHT.c_str());
    Button *button23 = new Button({0.880, 0.757, 0.201, 0.038}, UIElementDisplayText::LEFT_TRIGGER.c_str());
    Button *button24 = new Button({0.880, 0.711, 0.201, 0.038}, UIElementDisplayText::RIGHT_TRIGGER.c_str());
    Button *button25 = new Button({0.880, 0.666, 0.201, 0.038}, UIElementDisplayText::BUTTON_DOWN.c_str());
    Button *button26 = new Button({0.880, 0.574, 0.201, 0.038}, UIElementDisplayText::RIGHT_SHOULDER.c_str());
    Button *button27 = new Button({0.880, 0.483, 0.201, 0.038}, UIElementDisplayText::BUTTON_DOWN.c_str());
    Button *button28 = new Button({0.880, 0.392, 0.201, 0.038}, UIElementDisplayText::DMINUSPAD_DOWN.c_str());
    Button *button29 = new Button({0.880, 0.301, 0.201, 0.038}, UIElementDisplayText::LEFT_JOYSTICK_UP.c_str());
    Button *button30 = new Button({0.880, 0.255, 0.201, 0.038}, UIElementDisplayText::LEFT_JOYSTICK_LEFT.c_str());
    Button *button31 = new Button({0.880, 0.620, 0.201, 0.038}, UIElementDisplayText::BUTTON_RIGHT.c_str());
    Button *button32 = new Button({0.880, 0.529, 0.201, 0.038}, UIElementDisplayText::LEFT_SHOULDER.c_str());
    Button *button33 = new Button({0.880, 0.438, 0.201, 0.038}, UIElementDisplayText::BUTTON_UP.c_str());
    Button *button34 = new Button({0.880, 0.346, 0.201, 0.038}, UIElementDisplayText::LEFT_JOYSTICK_DOWN.c_str());
    Button *button35 = new Button({0.880, 0.209, 0.201, 0.038}, UIElementDisplayText::LEFT_JOYSTICK_RIGHT.c_str());
    Text *text19 = new Text({0.670, 0.081, 0.659, 0.094}, UIElementDisplayText::CONTROL.c_str());
    Text *text20 = new Text({0.166, 0.251, 0.330, 0.094}, UIElementDisplayText::GENERAL.c_str());
    Text *text21 = new Text({0.095, 0.362, 0.167, 0.045}, UIElementDisplayText::WINDOW_MODE.c_str());
    Text *text22 = new Text({0.249, 0.363, 0.086, 0.045}, UIElementDisplayText::CHANGABLE_TEXT.c_str());
    Button *button36 = new Button({0.192, 0.363, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_2.c_str());
    Button *button37 = new Button({0.306, 0.363, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_1.c_str());
    Text *text23 = new Text({0.095, 0.440, 0.167, 0.045}, UIElementDisplayText::MONITOR.c_str());
    Text *text24 = new Text({0.249, 0.441, 0.086, 0.045}, UIElementDisplayText::CHANGABLE_TEXT.c_str());
    Button *button38 = new Button({0.192, 0.441, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_2.c_str());
    Button *button39 = new Button({0.306, 0.441, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_1.c_str());
    Text *text25 = new Text({0.095, 0.517, 0.167, 0.045}, UIElementDisplayText::MAX_FRAMERATE.c_str());
    Text *text26 = new Text({0.249, 0.518, 0.086, 0.045}, UIElementDisplayText::CHANGABLE_TEXT.c_str());
    Button *button40 = new Button({0.192, 0.518, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_2.c_str());
    Button *button41 = new Button({0.306, 0.518, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_1.c_str());
    Text *text27 = new Text({0.095, 0.594, 0.167, 0.045}, UIElementDisplayText::MOUSE_SENSITIVITY.c_str());
    Text *text28 = new Text({0.249, 0.595, 0.086, 0.045}, UIElementDisplayText::CHANGABLE_TEXT.c_str());
    Button *button42 = new Button({0.192, 0.595, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_2.c_str());
    Button *button43 = new Button({0.306, 0.595, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_1.c_str());
    Text *text29 = new Text({0.095, 0.826, 0.167, 0.045}, UIElementDisplayText::CHANGABLE_TEXT.c_str());
    Text *text30 = new Text({0.249, 0.826, 0.086, 0.045}, UIElementDisplayText::CHANGABLE_TEXT.c_str());
    Button *button44 = new Button({0.192, 0.826, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_2.c_str());
    Button *button45 = new Button({0.306, 0.826, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_1.c_str());
    Text *text31 = new Text({0.095, 0.671, 0.167, 0.045}, UIElementDisplayText::CONTROLLER_THRESHOLD.c_str());
    Text *text32 = new Text({0.249, 0.672, 0.086, 0.045}, UIElementDisplayText::CHANGABLE_TEXT.c_str());
    Button *button46 = new Button({0.192, 0.672, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_2.c_str());
    Button *button47 = new Button({0.306, 0.672, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_1.c_str());
    Text *text33 = new Text({0.095, 0.748, 0.167, 0.045}, UIElementDisplayText::CHANGABLE_TEXT.c_str());
    Text *text34 = new Text({0.249, 0.749, 0.086, 0.045}, UIElementDisplayText::CHANGABLE_TEXT.c_str());
    Button *button48 = new Button({0.192, 0.749, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_2.c_str());
    Button *button49 = new Button({0.306, 0.749, 0.028, 0.049}, UIElementDisplayText::NO_TEXT_1.c_str());

    button1->SetNavigation(button44, nullptr, nullptr, button45);
    button2->SetNavigation(button3, nullptr, button45, button19);
    button3->SetNavigation(button4, button2, button45, button20);
    button4->SetNavigation(button5, button3, button45, button21);
    button5->SetNavigation(button6, button4, button45, button22);
    button6->SetNavigation(button7, button5, button49, button23);
    button7->SetNavigation(button8, button6, button49, button24);
    button8->SetNavigation(button14, button7, button47, button25);
    button9->SetNavigation(button15, button14, button43, button26);
    button10->SetNavigation(button16, button15, button41, button27);
    button11->SetNavigation(button17, button16, button37, button28);
    button12->SetNavigation(button13, button17, button37, button29);
    button13->SetNavigation(button18, button12, button37, button30);
    button14->SetNavigation(button9, button8, button43, button31);
    button15->SetNavigation(button10, button9, button41, button32);
    button16->SetNavigation(button11, button10, button39, button33);
    button17->SetNavigation(button12, button11, button37, button34);
    button18->SetNavigation(nullptr, button13, button37, button35);
    button19->SetNavigation(button20, nullptr, button2, nullptr);
    button20->SetNavigation(button21, button19, button3, nullptr);
    button21->SetNavigation(button22, button20, button4, nullptr);
    button22->SetNavigation(button23, button21, button5, nullptr);
    button23->SetNavigation(button24, button22, button6, nullptr);
    button24->SetNavigation(button25, button23, button7, nullptr);
    button25->SetNavigation(button31, button24, button8, nullptr);
    button26->SetNavigation(button32, button31, button9, nullptr);
    button27->SetNavigation(button33, button32, button10, nullptr);
    button28->SetNavigation(button34, button33, button11, nullptr);
    button29->SetNavigation(button30, button34, button12, nullptr);
    button30->SetNavigation(button35, button29, button13, nullptr);
    button31->SetNavigation(button26, button25, button14, nullptr);
    button32->SetNavigation(button27, button26, button15, nullptr);
    button33->SetNavigation(button28, button27, button16, nullptr);
    button34->SetNavigation(button29, button28, button17, nullptr);
    button35->SetNavigation(nullptr, button30, button18, nullptr);
    button36->SetNavigation(nullptr, button38, nullptr, button37);
    button37->SetNavigation(nullptr, button39, button36, button17);
    button38->SetNavigation(button36, button40, nullptr, button39);
    button39->SetNavigation(button37, button41, button38, button16);
    button40->SetNavigation(button38, button42, nullptr, button41);
    button41->SetNavigation(button39, button43, button40, button15);
    button42->SetNavigation(button40, button46, nullptr, button43);
    button43->SetNavigation(button41, button47, button42, button9);
    button44->SetNavigation(button48, button1, nullptr, button45);
    button45->SetNavigation(button49, nullptr, button44, button4);
    button46->SetNavigation(button42, button48, nullptr, button47);
    button47->SetNavigation(button43, button49, button46, button8);
    button48->SetNavigation(button46, button44, nullptr, button49);
    button49->SetNavigation(button47, button45, button48, button6);

    uiElements.push_back(button1);
    uiElements.push_back(text1);
    uiElements.push_back(text2);
    uiElements.push_back(text3);
    uiElements.push_back(text4);
    uiElements.push_back(text5);
    uiElements.push_back(text6);
    uiElements.push_back(text7);
    uiElements.push_back(text8);
    uiElements.push_back(text9);
    uiElements.push_back(text10);
    uiElements.push_back(text11);
    uiElements.push_back(text12);
    uiElements.push_back(text13);
    uiElements.push_back(text14);
    uiElements.push_back(text15);
    uiElements.push_back(text16);
    uiElements.push_back(text17);
    uiElements.push_back(text18);
    uiElements.push_back(button2);
    uiElements.push_back(button3);
    uiElements.push_back(button4);
    uiElements.push_back(button5);
    uiElements.push_back(button6);
    uiElements.push_back(button7);
    uiElements.push_back(button8);
    uiElements.push_back(button9);
    uiElements.push_back(button10);
    uiElements.push_back(button11);
    uiElements.push_back(button12);
    uiElements.push_back(button13);
    uiElements.push_back(button14);
    uiElements.push_back(button15);
    uiElements.push_back(button16);
    uiElements.push_back(button17);
    uiElements.push_back(button18);
    uiElements.push_back(button19);
    uiElements.push_back(button20);
    uiElements.push_back(button21);
    uiElements.push_back(button22);
    uiElements.push_back(button23);
    uiElements.push_back(button24);
    uiElements.push_back(button25);
    uiElements.push_back(button26);
    uiElements.push_back(button27);
    uiElements.push_back(button28);
    uiElements.push_back(button29);
    uiElements.push_back(button30);
    uiElements.push_back(button31);
    uiElements.push_back(button32);
    uiElements.push_back(button33);
    uiElements.push_back(button34);
    uiElements.push_back(button35);
    uiElements.push_back(text19);
    uiElements.push_back(text20);
    uiElements.push_back(text21);
    uiElements.push_back(text22);
    uiElements.push_back(button36);
    uiElements.push_back(button37);
    uiElements.push_back(text23);
    uiElements.push_back(text24);
    uiElements.push_back(button38);
    uiElements.push_back(button39);
    uiElements.push_back(text25);
    uiElements.push_back(text26);
    uiElements.push_back(button40);
    uiElements.push_back(button41);
    uiElements.push_back(text27);
    uiElements.push_back(text28);
    uiElements.push_back(button42);
    uiElements.push_back(button43);
    uiElements.push_back(text29);
    uiElements.push_back(text30);
    uiElements.push_back(button44);
    uiElements.push_back(button45);
    uiElements.push_back(text31);
    uiElements.push_back(text32);
    uiElements.push_back(button46);
    uiElements.push_back(button47);
    uiElements.push_back(text33);
    uiElements.push_back(text34);
    uiElements.push_back(button48);
    uiElements.push_back(button49);

    button1->OnClick = []()
    {
        InputManager::SetNavigationEnabled(false);
        InputManager::RemoveSelectedItem();
        RenderManager::TransitToNextScene(new MenuScene());
    };
}

void OptionScene::Enable()
{
    InputManager::SetNavigationEnabled(true);
    InputManager::SetSelectedItem(static_cast<Button *>(uiElements[0]));
}
