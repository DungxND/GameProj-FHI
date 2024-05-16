#ifndef UPGRADER_H
#define UPGRADER_H

#include "../graphics_n_audio.hpp"
#include "../input.hpp"


struct Upgrader
{
    Graphics* graphics{};
    Input* input{};
    Painter painter{};
    int x{}, y{}, w{}, h{}, mouseX{}, mouseY{}, textWidth{}, textHeight{}, maxLevel, size, upgradeBtnMenuLocation;
    string upgradeName, currency, description;
    SDL_Color upgradeBtnBGColor{}, upgradeBtnTextColor{}, upgradeBtnBorderColor{}, iconLevelColor = painter.white;
    bool isInfoOpened = false;
    bool isUpgradeBoardOpened = false;
    bool isTempUpgraded = false;

    Upgrader() = default;

    Upgrader(Graphics& graphics, Input& input, int size = 30, int x = 0, int y = 0, string upgradeName = "",
             string currency = "",
             string description = "", int maxLevel = 0, int upgradeBtnMenuLocation = 0);

    void draw_upgrade_icon(SDL_Texture* icon, int& availableMoney, int& currentLevel, int price,
                           int currentValue,
                           int nextValue);
};
#endif //UPGRADER_H
