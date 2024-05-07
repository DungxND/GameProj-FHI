#include "upgrader.hpp"

Upgrader::Upgrader(Graphics& graphics, Input& input, int w, int h, string upgradeName, string description, int price,
                   int level, int value, int nextValue, int maxLevel)
{
    this->graphics = graphics;
    this->input = &input;
    this->w = w;
    this->h = h;
    this->upgradeName = move(upgradeName);
    this->description = move(description);
    this->price = price;
    this->level = level;
    this->value = value;
    this->nextValue = nextValue;
    this->maxLevel = maxLevel;
}


void Upgrader::draw_upgrade_icon(SDL_Texture* icon, int level, int x, int y, int size)
{
    graphics.draw_rect(x, y, size, size, 3, painter.lightYellow, painter.black);
    graphics.render_texture(icon, x + 1, y + 1, size, size);
    graphics.draw_center_of_text(to_string(level).c_str(), 22, painter.white, x + size / 2,
                                 y + size + 25);
    if (input->mouse_x > x && input->mouse_x < x + size && input->mouse_y > y && input->mouse_y < y + size)
    {
        if (input->mouse_clicked)
        {
            isClicked = true;
        }
    }

    if (isClicked)
    {
        graphics.draw_rect(SCREEN_WIDTH * 0.71, SCREEN_HEIGHT * 0.1, SCREEN_WIDTH * 0.285, SCREEN_HEIGHT * 0.75, 3,
                           painter.brown, painter.white);
        graphics.draw_rect(SCREEN_WIDTH * 0.96, SCREEN_HEIGHT * 0.11, 40, 40, 3,
                           painter.brown, painter.white);
        graphics.draw_text("X", 30, painter.white, SCREEN_WIDTH * 0.96 + 7.5, SCREEN_HEIGHT * 0.11 + 5);

        graphics.draw_center_of_text(upgradeName.c_str(), 24, painter.white,
                                     SCREEN_WIDTH * 0.71 + SCREEN_WIDTH * 0.285 / 2,
                                     SCREEN_HEIGHT * 0.23);
        graphics.draw_center_of_text(("Level: " + to_string(level) + "/" + to_string(maxLevel)).c_str(), 17,
                                     painter.white,
                                     SCREEN_WIDTH * 0.71 + SCREEN_WIDTH * 0.285 / 2,
                                     SCREEN_HEIGHT * 0.28);
        graphics.draw_center_of_text(description.c_str(), 14, painter.white,
                                     SCREEN_WIDTH * 0.71 + SCREEN_WIDTH * 0.285 / 2,
                                     SCREEN_HEIGHT * 0.33);
        graphics.draw_center_of_text(("Current value: " + to_string(value)).c_str(), 15, painter.white,
                                     SCREEN_WIDTH * 0.71 + SCREEN_WIDTH * 0.285 / 2,
                                     SCREEN_HEIGHT * 0.5);
        graphics.draw_center_of_text(("Next value: " + to_string(nextValue)).c_str(), 15, painter.white,
                                     SCREEN_WIDTH * 0.71 + SCREEN_WIDTH * 0.285 / 2,
                                     SCREEN_HEIGHT * 0.55);


        if (input->mouse_x > SCREEN_WIDTH * 0.96 && input->mouse_x < SCREEN_WIDTH * 0.96 + 40 && input->mouse_y >
            SCREEN_HEIGHT * 0.11 && input->mouse_y < SCREEN_HEIGHT * 0.11 + 40)
        {
            if (input->mouse_clicked)
            {
                isClicked = false;
            }
        }
    }
}
