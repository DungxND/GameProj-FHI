
#ifndef _APP__H
#define _APP__H

#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include "defs.h"


using namespace std;

struct GameData {
    bool isFirstRun = true;
    int playTime = 0;
    int score = 0;
    int money = 0;
    int availableScoreBoxes = 0;
    int scoreBoxUpgrade = 1;
    int boxSpawnTimeUprade = 1;
    int sellPriceUpgrade = 1;
    bool boxArr[10][10] = {false};
    bool prevBoxArr[10][10] = {false};
    int openingTab = 1;

    void randomizeScoreBoxes() {
        while (availableScoreBoxes < scoreBoxUpgrade) {
            int x = rand() % 10;
            int y = rand() % 10;
            if (prevBoxArr[x][y] == false) {
                boxArr[x][y] = true;
                availableScoreBoxes++;
            }
        }
        copy(&boxArr[0][0], &boxArr[0][0] + 10 * 10, &prevBoxArr[0][0]);
    }

    void handleScoreBoxClick(int i, int j) {
        if (boxArr[i][j]) {
            boxArr[i][j] = false;
            score++;
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
