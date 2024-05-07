#ifndef UPGRADER_H
#define UPGRADER_H

#include "../graphics_n_audio.hpp"
#include "../input.hpp"

struct Upgrader
{
    Graphics graphics{};
    Input* input{};
    Painter painter{};
    int x{}, y{}, w{}, h{}, mouseX{}, mouseY{}, textWidth{}, textHeight{}, price{}, value{}, nextValue{}, level{},
        maxLevel{};
    string upgradeName, description;
    bool isInfoOpened = false;
    bool isClicked = false;

    Upgrader() = default;
    Upgrader(Graphics& graphics, Input& input, int w = 300, int h = 100, string upgradeName = "",
             string description = "",
             int price = 0, int level = 0, int value = 0, int nextValue = 0, int maxLevel = 0);


    void draw_upgrade_icon(SDL_Texture* icon, int level, int x, int y, int size);
};


#endif //UPGRADER_H
