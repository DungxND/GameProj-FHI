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
    Button startButton, moneyStat, scoreStat, scoreBoxButton, inactiveScoreBoxButton;
    GameData gameData;
    uint32_t startTime, currTime{}, lastSameTime = 0;

    bool running = true;
    bool shouldDestroy = false;
    bool oldTimeSet = false;
    int oldTime = 0;

    Game(): input(&saver, &gameData) {
        graphics.init();
        startTime = SDL_GetTicks();
        saver.load_data(&gameData);
        SDL_Delay(100);
        startButton = Button(input, 200, 100);
        moneyStat = Button(input, 200, 50);
        scoreStat = Button(input, 200, 50);
        scoreBoxButton = Button(input, MAINBOARD_WIDTH / 10, MAINBOARD_HEIGHT / 10);
        inactiveScoreBoxButton = Button(input, MAINBOARD_WIDTH / 10, MAINBOARD_HEIGHT / 10);
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
        string playTimeStr = "Play Time: " + to_string(gameData.playTime) + "s";
        startButton.draw(graphics,SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, "Start", 18, 5, painter.black, painter.red,
                         painter.white, true);
        startButton.handleClick(gameData);
        if (startButton.isDestroyed) {
            graphics.drawRect(SCREEN_WIDTH * 0.1, SCREEN_HEIGHT * 0.1, SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.7, 5,
                              painter.lightBrown, painter.brown, "Main Board");
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (gameData.boxArr[i][j]) {
                        Button tempButton = Button(input, MAINBOARD_WIDTH / 10, MAINBOARD_HEIGHT / 10,
                                                   to_string(i + j));
                        tempButton.drawDefaultOffset(graphics, SCREEN_WIDTH * 0.1 + i * MAINBOARD_WIDTH / 10,
                                                     SCREEN_HEIGHT * 0.1 + j * MAINBOARD_HEIGHT / 10, "", 1, 2,
                                                     painter.lightGreen,
                                                     painter.black);
                        tempButton.handleClick(gameData, true, i, j);
                    }
                }
            }
            graphics.drawRect(SCREEN_WIDTH * 0.7, 0, SCREEN_WIDTH * 0.3, SCREEN_HEIGHT, 3, painter.lightBrown,
                              painter.brown, "Side Board");

            graphics.drawText(playTimeStr.c_str(), 12, painter.white, SCREEN_WIDTH * 0.7 + 10, SCREEN_HEIGHT * 0.97);
            moneyStat.draw(graphics,SCREEN_WIDTH * 0.61, SCREEN_HEIGHT * 0.05, "Money: " + to_string(gameData.money),
                           12,
                           5, painter.grey, painter.green,
                           painter.white, false);
            scoreStat.draw(graphics,SCREEN_WIDTH * 0.61 - SCREEN_WIDTH * 0.17, SCREEN_HEIGHT * 0.05,
                           "Score: " + to_string(gameData.score),
                           12,
                           5, painter.grey, painter.green,
                           painter.white, false);
        } else {
            graphics.drawCenterOfText("SAI - Score Accumulating Incremental", 33, painter.white, SCREEN_WIDTH / 2,
                                      SCREEN_HEIGHT / 2 - 200);
        }
        graphics.drawRect(input.mouse_x, input.mouse_y, 7, 7, 1, painter.yellow, painter.grey);
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


#endif //SAI___SCORE_ACCUMULATING_INCREMENTAL_GAME_H
