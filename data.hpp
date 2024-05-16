#ifndef _APP__H
#define _APP__H

#include <SDL.h>
#include <cmath>
#include <iostream>

using namespace std;

struct GameData
{
    bool isFirstRun = true;
    bool musicShouldPlay = false;
    bool isBoxRespawnable = false;
    double playTime = 0;
    int level = 1;
    int xp = 1;
    int flower = 0;
    int perk = 0;
    int availableFlower = 0;
    int flowerValueUpgrade[2] = {1, 50};
    int flowerLimitUpgrade[2] = {1, 100};
    int flowerSpawnTimeUpgrade[2] = {1, 25};
    int musicSelection = 0;
    bool flowerArr[10][10] = {false};
    int openingTab = 1;
    // max volume = 128
    int musicVolume = 40;
    uint32_t lastSpawnTime = 0;


    int calc_flower_upgrade_cost()
    {
        return static_cast<int>(pow(1.475, flowerValueUpgrade[0])) + flowerValueUpgrade[0] * 10;
    }

    int calc_flower_value(int x)
    {
        return static_cast<int>(pow(1.35, x)) + (x - 1);
    }

    int calc_next_flower_value()
    {
        return calc_flower_value(flowerValueUpgrade[0] + 1);
    }

    int calc_flower_value()
    {
        return calc_flower_value(flowerValueUpgrade[0]);
    }

    int calc_spawn_time_upgrade_cost()
    {
        return static_cast<int>(pow(flowerSpawnTimeUpgrade[0] + 2, 2.8 + flowerSpawnTimeUpgrade[0] * 0.135)) +
            flowerSpawnTimeUpgrade
            [0] * 100;
    }

    double calc_spawn_time(int x)
    {
        if (x <= 25 && x > 0)
            return 3000 - 600 * sqrt(x);
        return 0;
    }

    int xp_to_next_level() const
    {
        return pow(level, 1.5) + level * 50;
    }

    int calc_earned_xp()
    {
        return 1;
    }

    double calc_next_spawn_time()
    {
        return calc_spawn_time(flowerSpawnTimeUpgrade[0] + 1);
    }

    double calc_spawn_time()
    {
        return calc_spawn_time(flowerSpawnTimeUpgrade[0]);
    }

    void randomize_flower_spawn(uint32_t currTime)
    {
        while (availableFlower < flowerLimitUpgrade[0] && (currTime - lastSpawnTime) > calc_spawn_time())
        {
            int x = rand() % 10;
            int y = rand() % 10;
            if (!flowerArr[x][y])
            {
                flowerArr[x][y] = true;
                availableFlower++;
                lastSpawnTime = currTime;
            }
        }
    }

    void xp_handler()
    {
        int earned_xp = calc_earned_xp();
        if (xp + earned_xp >= xp_to_next_level())
        {
            xp = xp + earned_xp - xp_to_next_level();
            level++;
            perk++;
        }
        else
        {
            xp += earned_xp;
        }
    }

    void handle_flower_click(int i, int j)
    {
        if (flowerArr[i][j])
        {
            flowerArr[i][j] = false;
            flower += calc_flower_value();
            xp_handler();
            availableFlower--;
        }
    }
};


struct Point
{
    int mouseX = 0;
    int mouseY = 0;
};


struct Painter
{
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
