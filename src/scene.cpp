#include "scene.hpp"
#include "ui.hpp"
#include <vector>
#include "setting.hpp"
#include "raylib.h"
#include "constants.hpp"

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
}

BlankScene::BlankScene()
{
}

TitleScene::TitleScene()
{
    Text *titleText = new Text({0.5f, 0.5f, 0.5f, 0.33f}, DisplayText::GAME_TITLE.c_str());
    Button *startButton = new Button({0.5f, 0.8f, 0.33f, 0.05f}, DisplayText::START_BUTTON_TEXT.c_str());

    uiElements.push_back(titleText);
    uiElements.push_back(startButton);
}

MenuScene::MenuScene()
{
    Text *titleText = new Text({0.25f, 0.25f, 0.5f, 0.33f}, DisplayText::GAME_TITLE.c_str());

    Button *switchThemeButton = new Button({0.1f, 0.8f, 0.18f, 0.1f}, DisplayText::SWITCH_THEME_BUTTON_TEXT.c_str());

    Button *soloButton = new Button({0.25f, 0.45f, 0.2f, 0.05f}, DisplayText::SOLO_BUTTON_TEXT.c_str());
    Button *localButton = new Button({0.25f, 0.55f, 0.2f, 0.05f}, DisplayText::LOCAL_BUTTON_TEXT.c_str());
    Button *onlineButton = new Button({0.25f, 0.65f, 0.2f, 0.05f}, DisplayText::ONLINE_BUTTON_TEXT.c_str());

    Button *fourtyLinesButton = new Button({0.5f, 0.45f, 0.2f, 0.05f}, DisplayText::FORTY_LINES_BUTTON_TEXT.c_str());
    Button *scoreAttackButton = new Button({0.5f, 0.55f, 0.2f, 0.05f}, DisplayText::SCORE_ATTACK_BUTTON_TEXT.c_str());
    Button *vsModeButton = new Button({0.5f, 0.65f, 0.2f, 0.05f}, DisplayText::VS_MODE_BUTTON_TEXT.c_str());

    Button *rankedMatchButton = new Button({0.5f, 0.45f, 0.2f, 0.05f}, DisplayText::RANKED_MATCH_BUTTON_TEXT.c_str());
    Button *customMatchButton = new Button({0.5f, 0.55f, 0.2f, 0.05f}, DisplayText::CUSTOM_MATCH_BUTTON_TEXT.c_str());

    Text *playerJoinText = new Text({0.85f, 0.78f, 0.3f, 0.05f}, DisplayText::PLAYER_JOIN_TEXT.c_str());
    Text *playerQuitText = new Text({0.85f, 0.83f, 0.3f, 0.05f}, DisplayText::PLAYER_QUIT_TEXT.c_str());

    soloButton->SetNavigation(nullptr, localButton, nullptr, nullptr);
    localButton->SetNavigation(soloButton, onlineButton, nullptr, nullptr);
    onlineButton->SetNavigation(localButton, nullptr, nullptr, nullptr);

    fourtyLinesButton->SetNavigation(nullptr, scoreAttackButton, nullptr, nullptr);
    scoreAttackButton->SetNavigation(fourtyLinesButton, vsModeButton, nullptr, nullptr);
    vsModeButton->SetNavigation(scoreAttackButton, nullptr, nullptr, nullptr);

    rankedMatchButton->SetNavigation(nullptr, customMatchButton, nullptr, nullptr);
    customMatchButton->SetNavigation(rankedMatchButton, nullptr, nullptr, nullptr);

    fourtyLinesButton->isVisible = false;
    scoreAttackButton->isVisible = false;
    vsModeButton->isVisible = false;

    rankedMatchButton->isVisible = false;
    customMatchButton->isVisible = false;

    uiElements.push_back(titleText);

    uiElements.push_back(switchThemeButton);

    uiElements.push_back(soloButton);
    uiElements.push_back(localButton);
    uiElements.push_back(onlineButton);

    uiElements.push_back(fourtyLinesButton);
    uiElements.push_back(scoreAttackButton);
    uiElements.push_back(vsModeButton);

    uiElements.push_back(rankedMatchButton);
    uiElements.push_back(customMatchButton);

    uiElements.push_back(playerJoinText);
    uiElements.push_back(playerQuitText);
}