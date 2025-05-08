#include "player.hpp"
#include "input.hpp"
#include <algorithm>
#include <vector>
#include <string>

std::vector<int> PlayerManager::playerIDs;

void PlayerManager::Init()
{
}

void PlayerManager::Update()
{
}

void PlayerManager::Unload()
{
}

int PlayerManager::GetPlayerCount()
{
    return playerIDs.size();
}

void PlayerManager::EnablePlayerJoin()
{
    InputManager::SetPauseCallback([](int playerID)
                                   {
        // if player join
        if(std::find(playerIDs.begin(), playerIDs.end(), playerID) == playerIDs.end())
        {
            playerIDs.push_back(playerID);
            TraceLog(LOG_INFO, "Player %d joined.", playerID);
        }
        else
        {
            playerIDs.erase(std::remove(playerIDs.begin(), playerIDs.end(), playerID), playerIDs.end());
        } });
}

void PlayerManager::DisablePlayerJoin()
{
    InputManager::RemovePauseCallback();
}

std::string PlayerManager::GetPlayerControllerName(int index)
{
    return InputManager::GetInputName(playerIDs[index]);
}