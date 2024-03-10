#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "../graphics.h"
#include "../defs.h"

struct Board {
    int x, y, w, h;
    bool isClicked = false;
    bool isHidden = false;

    Board(int x = SCREEN_WIDTH / 2, int y = SCREEN_HEIGHT / 2, int w = 0, int h = 0) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    void draw(Graphics &graphics, SDL_Color boxColor, SDL_Color borderColor) {
        if (!isHidden) {
            graphics.drawRect(x - 3, y - 3, w + 6, h + 6, borderColor);
            graphics.drawRect(x, y, w, h, boxColor);
        }
    }
};

#endif //BOARD_H
