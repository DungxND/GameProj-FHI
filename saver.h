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
            file << gameData->boxValueUpgrade[0] << "\n";
            file << gameData->boxAmmountUpgrade[0] << "\n";
            file << gameData->boxSpawnTimeUprade[0] << "\n";
            file << gameData->sellPriceUpgrade[0] << "\n";
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
            file >> gameData->boxValueUpgrade[0];
            file >> gameData->boxAmmountUpgrade[0];
            file >> gameData->boxSpawnTimeUprade[0];
            file >> gameData->sellPriceUpgrade[0];
            file.close();
            SDL_Log("Save data loaded!");
        } else {
            SDL_Log("No save file found");
        }
    }
};

#endif // SAI___SCORE_ACCUMULATING_INCREMENTAL_SAVER_H
