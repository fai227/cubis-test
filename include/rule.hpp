#pragma once

#include <string>

enum class GameMode
{
    FourtyLines,
    ScoreAttack,
    Versus,
};

class RuleManager
{
private:
    static GameMode gameMode;
    static int playerCount;

public:
    static void SetGameMode(GameMode mode);
    static GameMode GetNextGameMode(bool isNext);
    static GameMode GetGameMode();

    static void SetPlayerCount(int count);
    static int GetNextPlayerCount(bool isNext);
    static int GetPlayerCount();

    static std::string ConvertGameModeToString(GameMode mode);
    static std::string ConvertPlayerCountToString(int count);
};