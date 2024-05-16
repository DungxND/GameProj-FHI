#include "upgrader.hpp"

Upgrader::Upgrader(Graphics& graphics, Input& input, int size, int x, int y, string upgradeName, string currency,
                   string description, int maxLevel, int upgradeBtnMenuLocation)
{
    this->graphics = &graphics;
    this->input = &input;
    this->size = size;
    this->x = x;
    this->y = y;
    this->upgradeName = move(upgradeName);
    this->currency = move(currency);
    this->description = move(description);
    this->maxLevel = maxLevel;
    this->upgradeBtnMenuLocation = upgradeBtnMenuLocation;
}


void Upgrader::draw_upgrade_icon(SDL_Texture* icon, int& availableMoney, int& currentLevel,
                                 int price,
                                 int currentValue,
                                 int nextValue)
{
    if (graphics->aBoardOpenedInMenu != upgradeBtnMenuLocation && !isUpgradeBoardOpened)
    {
        graphics->draw_rect(x, y, size, size, 3, painter.lightYellow, painter.black);
        graphics->render_texture(icon, x + 1, y + 1, size, size);
        if (currentLevel < maxLevel)
        {
            iconLevelColor = painter.white;
        }
        else
        {
            iconLevelColor = painter.lightGrey;
        }
        if (price <= availableMoney)
        {
            iconLevelColor = painter.lightGreen;
        }
        graphics->draw_center_of_text(to_string(currentLevel).c_str(), 22, iconLevelColor, x + size / 2,
                                      y + size + 25);
        if (input->mouse_x > x && input->mouse_x < x + size && input->mouse_y > y && input->mouse_y < y + size)
        {
            if (input->mouse_clicked)
            {
                graphics->aBoardOpenedInMenu = upgradeBtnMenuLocation;
                isUpgradeBoardOpened = true;
            }
        }
    }
    if (isUpgradeBoardOpened)
    {
        graphics->draw_rect(SCREEN_WIDTH * 0.71, SCREEN_HEIGHT * 0.1, SCREEN_WIDTH * 0.285, SCREEN_HEIGHT * 0.75, 5,
                            painter.brown, painter.white);
        graphics->draw_rect(SCREEN_WIDTH * 0.96, SCREEN_HEIGHT * 0.11, 40, 40, 3,
                            painter.brown, painter.white);
        graphics->draw_text("X", 30, painter.white, SCREEN_WIDTH * 0.96 + 7.5, SCREEN_HEIGHT * 0.11 + 5);

        graphics->draw_center_of_text(upgradeName.c_str(), 22, painter.white,
                                      SCREEN_WIDTH * 0.71 + SCREEN_WIDTH * 0.285 / 2,
                                      SCREEN_HEIGHT * 0.23);
        graphics->draw_center_of_text(("Level: " + to_string(currentLevel) + "/" + to_string(maxLevel)).c_str(), 15,
                                      painter.white,
                                      SCREEN_WIDTH * 0.71 + SCREEN_WIDTH * 0.285 / 2,
                                      SCREEN_HEIGHT * 0.28);
        graphics->draw_center_of_text(description.c_str(), 12, painter.white,
                                      SCREEN_WIDTH * 0.71 + SCREEN_WIDTH * 0.285 / 2,
                                      SCREEN_HEIGHT * 0.33);
        graphics->draw_center_of_text(("Current value: " + to_string(currentValue)).c_str(), 13, painter.white,
                                      SCREEN_WIDTH * 0.71 + SCREEN_WIDTH * 0.285 / 2,
                                      SCREEN_HEIGHT * 0.5);
        graphics->draw_center_of_text(("Next value: " + to_string(nextValue)).c_str(), 13, painter.white,
                                      SCREEN_WIDTH * 0.71 + SCREEN_WIDTH * 0.285 / 2,
                                      SCREEN_HEIGHT * 0.55);

        graphics->draw_center_of_text(("Cost: " + to_string(price) + ' ' + currency).c_str(), 14, painter.white,
                                      SCREEN_WIDTH * 0.71 + SCREEN_WIDTH * 0.285 / 2, SCREEN_HEIGHT * 0.7);

        //handle color
        if (price <= availableMoney && currentLevel < maxLevel)
        {
            upgradeBtnBGColor = painter.brown;
            upgradeBtnBorderColor = painter.white;
            upgradeBtnTextColor = painter.white;
        }
        else
        {
            upgradeBtnBGColor = painter.lightBrown;
            upgradeBtnBorderColor = painter.darkGrey;
            upgradeBtnTextColor = painter.darkGrey;
        }

        //Close btn
        if (input->mouse_x > SCREEN_WIDTH * 0.96 && input->mouse_x < SCREEN_WIDTH * 0.96 + 40 && input->mouse_y >
            SCREEN_HEIGHT * 0.11 && input->mouse_y < SCREEN_HEIGHT * 0.11 + 40)
        {
            if (input->mouse_clicked)
            {
                graphics->aBoardOpenedInMenu = 0;
                isUpgradeBoardOpened = false;
            }
        }
        //Upgrade once btn
        if (input->mouse_x > SCREEN_WIDTH * 0.718 && input->mouse_x < SCREEN_WIDTH * 0.718 + SCREEN_WIDTH * 0.27 &&
            input->mouse_y > SCREEN_HEIGHT * 0.765 && input->mouse_y < SCREEN_HEIGHT * 0.765 + 60 && price <=
            availableMoney && currentLevel < maxLevel && !isTempUpgraded)
        {
            upgradeBtnBGColor = painter.darkBrown;
            if (input->mouse_clicked)
            {
                isTempUpgraded = true;
                currentLevel++;
                availableMoney -= price;
            }
            isTempUpgraded = false;
        }

        graphics->draw_rect(SCREEN_WIDTH * 0.718, SCREEN_HEIGHT * 0.765, SCREEN_WIDTH * 0.27, 60, 3,
                            upgradeBtnBGColor, upgradeBtnBorderColor);
        graphics->draw_center_of_text("Upgrade", 21, upgradeBtnTextColor,
                                      SCREEN_WIDTH * 0.718 + SCREEN_WIDTH * 0.27 / 2,
                                      SCREEN_HEIGHT * 0.805);
    }
}
