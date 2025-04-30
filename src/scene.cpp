#include "scene.hpp"
#include "ui.hpp"
#include <vector>

void Scene::Update()
{
    for (UIElement *element : uiElements)
    {
        if (element->isVisible)
        {
            element->Draw();
        }
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
    // UI要素の初期化
    uiElements.push_back(new Text({10, 10, 200, 50}, "Blank Scene"));
    uiElements.push_back(new Button({10, 70, 200, 50}, "Button 1"));
    uiElements.push_back(new Button({10, 130, 200, 50}, "Button 2"));
}
