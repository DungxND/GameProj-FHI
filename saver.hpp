#ifndef FHI_Flower_Harvesting_Inc_SAVER_H
#define FHI_Flower_Harvesting_Inc_SAVER_H

#include <fstream>
#include <string>
#include "data.hpp"

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
            file << gameData->musicShouldPlay << "\n";
            file << gameData->playTime << "\n";
            file << gameData->level << "\n";
            file << gameData->xp << "\n";
            file << gameData->flower << "\n";
            file << gameData->perk << "\n";
            file << gameData->flowerValueUpgrade[0] << "\n";
            file << gameData->flowerLimitUpgrade[0] << "\n";
            file << gameData->flowerSpawnTimeUpgrade[0] << "\n";
            file << gameData->musicSelection << "\n";
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
            file >> gameData->musicShouldPlay;
            file >> gameData->playTime;
            file >> gameData->level;
            file >> gameData->xp;
            file >> gameData->flower;
            file >> gameData->perk;
            file >> gameData->flowerValueUpgrade[0];
            file >> gameData->flowerLimitUpgrade[0];
            file >> gameData->flowerSpawnTimeUpgrade[0];
            file >> gameData->musicSelection;
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

#endif // FHI_Flower_Harvesting_Inc_SAVER_H
