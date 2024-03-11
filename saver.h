#ifndef SAI___SCORE_ACCUMULATING_INCREMENTAL_SAVER_H
#define SAI___SCORE_ACCUMULATING_INCREMENTAL_SAVER_H

#include <fstream>
#include <string>
#include "structs.h"

using namespace std;

struct Saver {
    string filename = "savefile.txt";

    void save_data(GameData *gameData) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << gameData->isFirstRun << "\n";
            file << gameData->playTime << "\n";
            file << gameData->score << "\n";
            file << gameData->money << "\n";
            file << gameData->scoreBoxUpgrade << "\n";
            file << gameData->boxSpawnTimeUprade << "\n";
            file << gameData->sellPriceUpgrade << "\n";
            file.close();
            SDL_Log("Game saved!");
        } else {
            SDL_Log("Saving failed!");
        }
    }


    void load_data(GameData *gameData) const {
        ifstream file(filename);
        if (file.is_open()) {
            file >> gameData->isFirstRun;
            file >> gameData->playTime;
            file >> gameData->score;
            file >> gameData->money;
            file >> gameData->scoreBoxUpgrade;
            file >> gameData->boxSpawnTimeUprade;
            file >> gameData->sellPriceUpgrade;
            file.close();
            SDL_Log("Save data loaded!");
        } else {
            SDL_Log("No save file found");
        }
    }
};

#endif // SAI___SCORE_ACCUMULATING_INCREMENTAL_SAVER_H
