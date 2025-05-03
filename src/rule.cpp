#include "rule.hpp"

#include "magic_enum.hpp"
#include "constants.hpp"
#include "raylib.h"

GameMode RuleManager::gameMode = GameMode::FourtyLines;
int RuleManager::playerCount = 1;

void RuleManager::SetGameMode(GameMode mode)
{
    gameMode = mode;
}

GameMode RuleManager::GetNextGameMode(bool isNext)
{
    int count = magic_enum::enum_count<GameMode>();
    if (isNext)
    {
        return static_cast<GameMode>((static_cast<int>(gameMode) + 1) % count);
    }
    else
    {
        return static_cast<GameMode>((static_cast<int>(gameMode) - 1 + count) % count);
    }
}

GameMode RuleManager::GetGameMode()
{
    return gameMode;
}

void RuleManager::SetPlayerCount(int count)
{
    playerCount = count;
}

int RuleManager::GetNextPlayerCount(bool isNext)
{
    if (isNext)
    {
        return (playerCount % Constants::MAX_PLAYER_COUNT) + 1;
    }
    else
    {
        return (playerCount - 2 + Constants::MAX_PLAYER_COUNT) % Constants::MAX_PLAYER_COUNT + 1;
    }
}

int RuleManager::GetPlayerCount()
{
    return playerCount;
}

std::string RuleManager::ConvertGameModeToString(GameMode mode)
{
    switch (mode)
    {
    case GameMode::FourtyLines:
        return GameText::FOURTY_LINES;
    case GameMode::ScoreAttack:
        return GameText::SCORE_ATTACK;
    case GameMode::Versus:
        return GameText::VERSUS;
    }

    TraceLog(LOG_WARNING, "RuleManager::ConvertGameModeToString: Invalid game mode: %d", static_cast<int>(mode));
    return GameText::FOURTY_LINES;
}

std::string RuleManager::ConvertPlayerCountToString(int count)
{
    return std::to_string(count);
}