
#ifndef _APP__H
#define _APP__H

#include <SDL.h>
#include <cmath>
#include <iostream>
#include <vector>


using namespace std;

struct GameData {
    bool isFirstRun = true;
    bool isBoxRespawnable = false;
    double playTime = 0;
    int score = 0;
    int money = 0;
    int availableScoreBoxes = 0;
    int boxValueUpgrade[2] = {1, 50};
    int boxAmmountUpgrade[2] = {1, 100};
    int boxSpawnTimeUprade[2] = {1, 25};
    int sellPriceUpgrade[2] = {1, 25};
    bool boxArr[10][10] = {false};
    int openingTab = 1;
    uint32_t lastSpawnTime = 0;


    int calBoxUpgradeCost() {
        return static_cast<int>(pow(1.4, boxValueUpgrade[0]));
    }

    int calBoxValue(int x) {
        return static_cast<int>(pow(1.35, x));
    }

    int calBoxValue() {
        return calBoxValue(boxValueUpgrade[0]);
    }

    int calSpawnTimeUpgradeCost() {
        return static_cast<int>(pow(1.55, boxSpawnTimeUprade[0]) - sqrt(pow(1.6, boxSpawnTimeUprade[0])));
    }

    double calSpawnTime(int x) {
        if (x <= 25 && x > 0)
            return 3000 - 600 * sqrt(x);
        return 0;
    }

    double calSpawnTime() {
        return calSpawnTime(boxSpawnTimeUprade[0]);
    }

    void randomizeScoreBoxes(uint32_t currTime) {
        while (availableScoreBoxes < boxAmmountUpgrade[0] && (currTime - lastSpawnTime) > calSpawnTime()) {
            int x = rand() % 10;
            int y = rand() % 10;
            if (!boxArr[x][y]) {
                boxArr[x][y] = true;
                availableScoreBoxes++;
                lastSpawnTime = currTime;
            }
        }
    }

    void handleScoreBoxClick(int i, int j) {
        if (boxArr[i][j]) {
            boxArr[i][j] = false;
            score += calBoxValue();
            availableScoreBoxes--;
        }
    }
};


struct Point {
    int mouseX = 0;
    int mouseY = 0;
};


struct Painter {
    SDL_Color white = {255, 255, 255, 255}, black = {0, 0, 0, 255}, green = {0, 255, 0, 255}, red = {255, 0, 0, 255},
            blue = {0, 0, 255, 255}, orange = {255, 165, 0, 255}, yellow = {255, 255, 0, 255},
            purple = {128, 0, 128, 255}, cyan = {0, 255, 255, 255}, pink = {255, 192, 203, 255},
            brown = {89, 75, 70, 255}, darkBrown = {56, 48, 45, 255}, grey = {128, 128, 128, 255},
            lightGrey = {211, 211, 211, 255}, darkGrey = {169, 169, 169, 255}, lightBlue = {173, 216, 230, 255},
            lightGreen = {144, 238, 144, 255}, lightPink = {255, 182, 193, 255}, lightYellow = {255, 255, 224, 255},
            lightPurple = {221, 160, 221, 255}, lightCyan = {224, 255, 255, 255}, lightBrown = {120, 103, 97, 255},
            lightOrange = {255, 160, 122, 255}, lightRed = {255, 99, 71, 255};
};
#endif // _APP__H
