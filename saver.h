#ifndef SAI___SCORE_ACCUMULATING_INCREMENTAL_SAVER_H
#define SAI___SCORE_ACCUMULATING_INCREMENTAL_SAVER_H

#include "structs.h"
#include <fstream>
#include <string>

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
            file << gameData->scoreBox << "\n";
            file.close();
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
            file >> gameData->scoreBox;
            file.close();
        } else {
            SDL_Log("No save file found");
        }
    }
};

#endif //SAI___SCORE_ACCUMULATING_INCREMENTAL_SAVER_H
