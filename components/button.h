#ifndef SAI___SCORE_ACCUMULATING_INCREMENTAL_BUTTON_H
#define SAI___SCORE_ACCUMULATING_INCREMENTAL_BUTTON_H

#include <string>
#include "../graphics.h"

using namespace std;


struct Button {
    Input *input{};
    int x{}, y{}, w{}, h{}, mouseX{}, mouseY{}, textWidth{}, textHeight{};
    bool isClicked = false;
    bool isDestroyed = false;
    string name;

    Button() = default;

    Button(Input &input, int w = 300, int h = 100, string name = "") {
        this->input = &input;
        this->w = w;
        this->h = h;
        this->name = move(name);
    }


    void handleClick(GameData &gameData, bool handleBox = false, int i = 0, int j = 0) {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x - w / 2 && mouseX <= x + w / 2 && mouseY >= y - h / 2 &&
            mouseY <= y + h / 2) {
            isDestroyed = true;
            if (handleBox)
                gameData.handleScoreBoxClick(i, j);
        }
    }

    void handleDefaultOffetClick(GameData &gameData, bool handleBox = false, int i = 0, int j = 0) {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h) {
            isDestroyed = true;
            if (handleBox)
                gameData.handleScoreBoxClick(i, j);
        }
    }

    void handleTabClick(GameData &gameData, int tabValue) {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h) {
            gameData.openingTab = tabValue;
        }
    }

    void draw(Graphics &graphics, int _x, int _y, const string &text = "", int fontSize = 16, int borderThickness = 0,
              SDL_Color boxColor = {0, 0, 0, 0}, SDL_Color borderColor = {0, 0, 0, 0},
              SDL_Color textColor = {0, 0, 0, 0}, bool destroyable = true, SDL_Texture *texture = nullptr) {
        x = _x;
        y = _y;
        if (!isDestroyed) {
            graphics.drawRect(x - w / 2, y - h / 2, w, h, borderThickness, boxColor, borderColor);
            if (texture != nullptr)
                graphics.renderCenterOfTexture(texture, x, y, w, h);
            if (!text.empty()) {
                TTF_SizeText(graphics.PrStart, text.c_str(), &textWidth, &textHeight);
                graphics.drawCenterOfText(text.c_str(), fontSize, textColor, x, y);
            }
        }
    }

    void drawDefaultOffset(Graphics &graphics, int _x, int _y, const string &text = "", int fontSize = 16,
                           int borderThickness = 0, SDL_Color boxColor = {0, 0, 0, 0},
                           SDL_Color borderColor = {0, 0, 0, 0}, SDL_Color textColor = {0, 0, 0, 0},
                           bool destroyable = true, SDL_Texture *texture = nullptr) {
        x = _x;
        y = _y;
        if (!isDestroyed) {
            graphics.drawRect(x, y, w, h, borderThickness, boxColor, borderColor);
            if (texture != nullptr) {
                int imgW = w * 2 / 3, imgH = h * 2 / 3;
                graphics.renderCenterOfTexture(texture, x + w / 2, y + h / 2, imgW, imgH);
            }
            if (!text.empty()) {
                TTF_SizeText(graphics.PrStart, text.c_str(), &textWidth, &textHeight);
                graphics.drawCenterOfText(text.c_str(), fontSize, textColor, x, y);
            }
        }
    }
};

#endif // SAI___SCORE_ACCUMULATING_INCREMENTAL_BUTTON_H
