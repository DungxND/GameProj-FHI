#ifndef SAI___SCORE_ACCUMULATING_INCREMENTAL_GAME_H
#define SAI___SCORE_ACCUMULATING_INCREMENTAL_GAME_H

#include <SDL.h>
#include "graphics.h"
#include "input.h"
#include "components/button.h"
#include "saver.h"

using namespace std;

struct Game {
    Graphics graphics{};
    Saver saver;
    Input input;
    Painter painter;
    Button startButton, moneyStat, scoreStat, scoreBoxButton, inactiveScoreBoxButton, upgradeTabMenu, sellingTabMenu,
            settingTabMenu;
    GameData gameData;
    uint32_t startTime, currTime{}, lastSameTime = 0;

    bool running = true;
    bool shouldDestroy = false;
    bool oldTimeSet = false;
    int oldTime = 0;
    SDL_Texture *upgradeIcon, *moneyIcon, *settingIcon, *ApScore;

    Game() : input(&saver, &gameData) {
        graphics.init();
        startTime = SDL_GetTicks();
        saver.load_data(&gameData);
        SDL_Delay(100);
        startButton = Button(input, 200, 100);
        moneyStat = scoreStat = Button(input, 200, 50);
        scoreBoxButton = inactiveScoreBoxButton = Button(input, MAINBOARD_WIDTH / 10, MAINBOARD_HEIGHT / 10);
        upgradeTabMenu = sellingTabMenu = settingTabMenu =
                                          Button(input, SIDEBOARD_WIDTH * 0.25, SIDEBOARD_HEIGHT * 0.1);
        ApScore = graphics.loadTexture("assets/img/ApScore.png");
        upgradeIcon = graphics.loadTexture("assets/img/upgrade.png");
        moneyIcon = graphics.loadTexture("assets/img/moneySymbol.png");
        settingIcon = graphics.loadTexture("assets/img/gearIcon.png");
    }

    void run() {
        while (running) {
            timer();
            graphics.prepareScene();
            checkIfEsc();
            drawNHendleElements();
            input.get();
            graphics.presentScene();
            gameData.randomizeScoreBoxes();
            saveGame();
        }
        saveGame();
        gameData.isFirstRun = false;
        graphics.quit();
    }

    void drawNHendleElements() {
        startButton.draw(graphics, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, "Start", 18, 5, painter.black, painter.red,
                         painter.white, true);
        startButton.handleClick(gameData);
        if (startButton.isDestroyed) {
            drawMainBoard();
            drawSideBoard();
            drawStat();
        } else {
            graphics.drawCenterOfText("SAI - Score Accumulating Incremental", 33, painter.white, SCREEN_WIDTH / 2,
                                      SCREEN_HEIGHT / 2 - 200);
        }
        graphics.drawRect(input.mouse_x, input.mouse_y, 7, 7, 1, painter.yellow, painter.grey);
    }

    void drawMainBoard() {
        graphics.drawRect(SCREEN_WIDTH * 0.12, SCREEN_HEIGHT * 0.13, SCREEN_WIDTH * 0.52, SCREEN_HEIGHT * 0.77, 5,
                          painter.darkBrown, painter.brown, "Main Board");
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (gameData.boxArr[i][j]) {
                    Button tempBtn = scoreBoxButton;
                    tempBtn.drawDefaultOffset(graphics, SCREEN_WIDTH * 0.13 + i * MAINBOARD_WIDTH / 10,
                                              SCREEN_HEIGHT * 0.15 + j * (MAINBOARD_HEIGHT / 10 + 1), "", 1, 2,
                                              painter.lightGreen, painter.black);
                    tempBtn.handleDefaultOffetClick(gameData, true, i, j);
                } else {
                    Button tempunBtn = inactiveScoreBoxButton;
                    tempunBtn.drawDefaultOffset(graphics, SCREEN_WIDTH * 0.13 + i * MAINBOARD_WIDTH / 10,
                                                SCREEN_HEIGHT * 0.15 + j * MAINBOARD_HEIGHT / 10, "", 1, 2,
                                                painter.lightBrown, painter.black);
                }
            }
        }
    }

    void drawSideBoard() {
        graphics.drawRect(SCREEN_WIDTH * 0.7, 0, SIDEBOARD_WIDTH, SIDEBOARD_HEIGHT, 3, painter.lightBrown,
                          painter.brown, "Side Board");
        upgradeTabMenu.drawDefaultOffset(graphics, SCREEN_WIDTH * (0.7) + 15, SCREEN_HEIGHT * 0.88, "", 0, 3,
                                         painter.brown, painter.black, painter.white, false, upgradeIcon);
        upgradeTabMenu.handleTabClick(gameData, 1);
        sellingTabMenu.drawDefaultOffset(graphics, SCREEN_WIDTH * (0.7 + 0.3 * 1 / 3) + 15, SCREEN_HEIGHT * 0.88, "", 0,
                                         3, painter.brown, painter.black, painter.white, false, moneyIcon);
        sellingTabMenu.handleTabClick(gameData, 2);
        settingTabMenu.drawDefaultOffset(graphics, SCREEN_WIDTH * (0.7 + 0.3 * 2 / 3) + 15, SCREEN_HEIGHT * 0.88, "", 0,
                                         3, painter.brown, painter.black, painter.white, false, settingIcon);
        settingTabMenu.handleTabClick(gameData, 3);
        switch (gameData.openingTab) {
            case 1:
                upgradeTabMenu.drawDefaultOffset(graphics, SCREEN_WIDTH * (0.7) + 15, SCREEN_HEIGHT * 0.88, "", 0, 3,
                                                 painter.darkBrown, painter.black, painter.white, false, upgradeIcon);
                break;
            case 2:
                sellingTabMenu.drawDefaultOffset(graphics, SCREEN_WIDTH * (0.7 + 0.3 * 1 / 3) + 15,
                                                 SCREEN_HEIGHT * 0.88, "", 0, 3, painter.darkBrown, painter.black,
                                                 painter.white, false, moneyIcon);
                break;
            case 3:
                settingTabMenu.drawDefaultOffset(graphics, SCREEN_WIDTH * (0.7 + 0.3 * 2 / 3) + 15,
                                                 SCREEN_HEIGHT * 0.88, "", 0, 3, painter.darkBrown, painter.black,
                                                 painter.white, false, settingIcon);
                string playTimeStr = "Play Time: " + to_string(gameData.playTime) + "s";
                graphics.drawText(playTimeStr.c_str(), 12, painter.white, SCREEN_WIDTH * 0.7 + 10,
                                  SCREEN_HEIGHT * 0.83);
                break;
        }
    }

    void drawStat() {
        moneyStat.draw(graphics, SCREEN_WIDTH * 0.61, SCREEN_HEIGHT * 0.05, "Money: " + to_string(gameData.money), 12,
                       5, painter.grey, painter.green, painter.white, false);
        scoreStat.draw(graphics, SCREEN_WIDTH * 0.61 - SCREEN_WIDTH * 0.17, SCREEN_HEIGHT * 0.05,
                       "Score: " + to_string(gameData.score), 12, 5, painter.grey, painter.green, painter.white, false);
    }

    void timer() {
        currTime = SDL_GetTicks();
        if (!oldTimeSet) {
            oldTime = gameData.playTime;
            SDL_Log("Old time: %d", oldTime);
            oldTimeSet = true;
        }
        gameData.playTime = (currTime - startTime) / 1000 + oldTime;
    }

    void saveGame() {
        if (gameData.playTime % 30 == 0 && gameData.playTime != 0 && gameData.playTime != lastSameTime || !running) {
            SDL_Log("Player play time: %d", gameData.playTime);
            saver.save_data(&gameData);
            lastSameTime = gameData.playTime;
        }
    }

    void checkIfEsc() {
        if (input.isKeyDown(SDL_SCANCODE_ESCAPE)) {
            running = false;
            SDL_Log("Exiting...");
            SDL_Delay(100);
        }
    }
};


#endif // SAI___SCORE_ACCUMULATING_INCREMENTAL_GAME_H
