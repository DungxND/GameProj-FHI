#ifndef SAI___SCORE_ACCUMULATING_INCREMENTAL_SAVER_H
#define SAI___SCORE_ACCUMULATING_INCREMENTAL_SAVER_H

#include <fstream>
#include <string>
#include "structs.hpp"

using namespace std;

struct Saver
{
    string filename = "savefile.txt";

    void save_data(GameData* gameData) const
    {
        ofstream file(filename);
        if (file.is_open())
        {
            file << gameData->isFirstRun << "\n";
            file << gameData->musicPlaying << "\n";
            file << gameData->playTime << "\n";
            file << gameData->level << "\n";
            file << gameData->xp << "\n";
            file << gameData->score << "\n";
            file << gameData->perk << "\n";
            file << gameData->flowerValueUpgrade[0] << "\n";
            file << gameData->flowerLimitUpgrade[0] << "\n";
            file << gameData->flowerSpawnTimeUpgrade[0] << "\n";
            file << gameData->musicVolume << "\n";
            file.close();
            SDL_Log("Game saved!");
        }
        else
        {
            SDL_Log("Saving failed!");
        }
    }


    void load_data(GameData* gameData) const
    {
        ifstream file(filename);
        if (file.is_open())
        {
            file >> gameData->isFirstRun;
            file >> gameData->musicPlaying;
            file >> gameData->playTime;
            file >> gameData->level;
            file >> gameData->xp;
            file >> gameData->score;
            file >> gameData->perk;
            file >> gameData->flowerValueUpgrade[0];
            file >> gameData->flowerLimitUpgrade[0];
            file >> gameData->flowerSpawnTimeUpgrade[0];
            file >> gameData->musicVolume;
            file.close();
            SDL_Log("Save data loaded!");
        }
        else
        {
            SDL_Log("No save file found");
        }
    }
};

#endif // SAI___SCORE_ACCUMULATING_INCREMENTAL_SAVER_H
