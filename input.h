#include <SDL.h>
#include "defs.h"
#include "structs.h"
#include "graphics.h"
#include "saver.h"

using namespace std;

struct Input {
    Graphics graphics{};
    Saver *saver;
    GameData *gameData;

    int keyboard[MAX_KEYBOARD_KEYS] = {0};
    int mouse_x = 0, mouse_y = 0;
    bool mouse_clicked = false;

    Input(Saver *saver, GameData *gameData) : saver(saver), gameData(gameData) {
        for (int &i: keyboard) i = 0;
    }

    void get() {
        SDL_PumpEvents();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    saver->save_data(gameData);
                    SDL_Log("Exiting...");
                    SDL_Delay(100);
                    exit(0);
                    break;
                case SDL_KEYDOWN:
                    if (event.key.repeat == 0
                        && event.key.keysym.scancode < MAX_KEYBOARD_KEYS) {
                        keyboard[event.key.keysym.scancode] = 1;
                    }
                    break;
                case SDL_KEYUP:
                    if (event.key.repeat == 0
                        && event.key.keysym.scancode < MAX_KEYBOARD_KEYS) {
                        keyboard[event.key.keysym.scancode] = 0;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouse_x = event.button.x;
                    mouse_y = event.button.y;
                    mouse_clicked = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouse_clicked = false;
                    break;
                default:
                    break;
            }
        }
    }

    bool isKeyDown(SDL_Scancode key) const {
        return keyboard[key];
    }

    //getmouselocation
    Point getMouseLocation() const {
        return {mouse_x, mouse_y};
    }
};
