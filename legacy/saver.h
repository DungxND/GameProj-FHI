#ifndef FHI_Flower_Harvesting_Inc_SAVER_H
#define FHI_Flower_Harvesting_Inc_SAVER_H

#include "structs.h"
#include <string>
#include <SDL.h>

struct Saver {
    SDL_RWops *file;

    Saver() {
        file = SDL_RWFromFile("savefile.bin", "r+b");
        if (file == nullptr) {
            SDL_Log("Failed to open file for writing! Creating new file");
            file = SDL_RWFromFile("savefile.bin", "w+b");
            if (file == nullptr) {
                SDL_Log("Failed to create new file!");
            }
        }
    }

    ~Saver() {
        if (file != nullptr) {
            SDL_RWclose(file);
        }
    }

    void save_data(Player *player) const {
        if (file != nullptr) {
            SDL_RWwrite(file, &(player->playTime), sizeof(player->playTime), 1);
            SDL_RWwrite(file, &(player->isFirstRun), sizeof(player->isFirstRun), 1);
            SDL_Log("Data saved!, play time: %d", player->playTime);
        } else {
            SDL_Log("Saving failed!");
        }
    }

    void load_data(Player *player) const {
        if (file != nullptr) {
            SDL_RWread(file, &(player->playTime), sizeof(player->playTime), 1);
            SDL_RWread(file, &(player->isFirstRun), sizeof(player->isFirstRun), 1);
            SDL_Log("Data loaded!, play time: %d", player->playTime);
        } else {
            SDL_Log("No save file found");
        }
    }
};

#endif //FHI_Flower_Harvesting_Inc_SAVER_H
