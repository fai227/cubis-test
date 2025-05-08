#pragma once

#include <string>
#include <vector>

class PlayerManager
{
private:
    static std::vector<int> playerIDs;

public:
    static void Init();
    static void Update();
    static void Unload();

    static int GetPlayerCount();
    static void EnablePlayerJoin();
    static void DisablePlayerJoin();

    static std::string GetPlayerControllerName(int index);
};
