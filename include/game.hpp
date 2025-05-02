#pragma once

class Game
{
private:
    static void Init();
    static void Mainloop();
    static void Unload();

    static bool shouldExit;

public:
    static void Run();
    static void RequestExit();
};