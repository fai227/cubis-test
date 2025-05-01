#pragma once

#include <functional>

class SystemManager
{
private:
    static int previousWidth;
    static int previousHeight;
    static std::function<void(int width, int height)> windowResizeCallback;

public:
    static void Init();
    static void Update();
    static void Unload();

    static void SetWindowResizeCallback(std::function<void(int width, int height)> callback);
};