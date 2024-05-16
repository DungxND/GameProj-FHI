#ifndef FHI_Flower_Harvesting_Inc_BUTTON_H
#define FHI_Flower_Harvesting_Inc_BUTTON_H

#include <string>
#include <iostream>
#include "../graphics_n_audio.hpp"

using namespace std;


struct Button
{
    Graphics graphics{};
    Input* input{};
    Painter painter{};
    int x{}, y{}, w{}, h{}, mouseX{}, mouseY{}, textWidth{}, textHeight{};
    bool isClicked = false;
    bool isHovering = false;
    bool isUpgraded = false;
    bool isPressed = false;
    bool isDestroyed = false;
    bool upgradeInfoOpening = false, flip = false;
    string name;

    Button() = default;

    Button(Graphics& graphics, Input& input, int w = 300, int h = 100, string name = "", bool flip = false)
    {
        this->graphics = graphics;
        this->input = &input;
        this->w = w;
        this->h = h;
        this->name = move(name);
        this->flip = flip;
    }


    void handle_click(GameData& gameData, bool handleBox = false, int i = 0, int j = 0)
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x - w / 2 && mouseX <= x + w / 2 && mouseY >= y - h / 2 &&
            mouseY <= y + h / 2)
        {
            isDestroyed = true;
            if (handleBox)
                gameData.handle_flower_click(i, j);
        }
    }

    void handle_upgrade_click(auto& data, auto& currency, int price)
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        isPressed = input->mouse_clicked;
        if (input->mouse_clicked && !isUpgraded && currency >= price && data[0] < data[1] && mouseX >= x &&
            mouseX <= x + w && mouseY >= y &&
            mouseY <= y + h)
        {
            ++data[0];
            currency -= price;
            isUpgraded = true;
        }
        if (!input->mouse_clicked)
        {
            isPressed = false;
            isUpgraded = false;
        }
    }

    void handle_default_offset_click(GameData& gameData, bool handleBox = false, int i = 0, int j = 0)
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h)
        {
            isDestroyed = true;
            if (handleBox)
                gameData.handle_flower_click(i, j);
        }
    }

    void handle_tab_click(GameData& gameData, int tabValue)
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h)
        {
            gameData.openingTab = tabValue;
        }
    }


    bool handle_hover()
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h)
        {
            isHovering = true;
        }
        else
        {
            isHovering = false;
        }
        return isHovering;
    }

    void handle_music_click(GameData& gameData, bool& musicPaused)
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && !isClicked && mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h)
        {
            if (gameData.musicShouldPlay && !musicPaused)
            {
                gameData.musicShouldPlay = false;
                Mix_PauseMusic();
                musicPaused = true;
                SDL_Log("Music paused");
            }
            else
            {
                gameData.musicShouldPlay = true;
                Mix_ResumeMusic();
                musicPaused = false;
                SDL_Log("Music resumed/started");
            }
            isClicked = true;
        }
        if (!input->mouse_clicked)
        {
            isClicked = false;
        }
    }


    void handle_next_song_click(GameData& gameData)
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h && isClicked ==
            false
        )
        {
            gameData.musicSelection = (gameData.musicSelection + 1) % 4;
            isClicked = true;
        }
        if (!input->mouse_clicked)
        {
            isClicked = false;
        }
    }

    void handle_prev_song_click(GameData& gameData)
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h && isClicked ==
            false)
        {
            gameData.musicSelection = (gameData.musicSelection + 3) % 4;
            isClicked = true;
        }
        if (!input->mouse_clicked)
        {
            isClicked = false;
        }
    }

    void handle_map_click(int& mapValue, int inpMap)
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h && !isClicked)
        {
            mapValue = inpMap;
            isClicked = true;
        }
        if (!input->mouse_clicked)
        {
            isClicked = false;
        }
    }

    void handle_volume_slider(GameData& gameData)
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h)
        {
            gameData.musicVolume = (mouseX * 1.0 - x * 1.0) / w * 128.0;
        }
        if (input->mouse_clicked && mouseX >= x + w && mouseX <= x + w + 15 && mouseY >= y && mouseY <= y + h)
        {
            gameData.musicVolume = 128;
        }
        if (input->mouse_clicked && mouseX >= x - 15 && mouseX <= x && mouseY >= y && mouseY <= y + h)
        {
            gameData.musicVolume = 0;
        }
        graphics.draw_rect(x + 2, y + 2, (w - 4) * (gameData.musicVolume / 128.0), h - 4, 0, painter.orange);
        graphics.draw_text(("Volume: " + to_string(static_cast<int>(gameData.musicVolume / 128.0 * 100)) +
                               "%").c_str(), 16, painter.white, x + 10, y + h / 2);
    }

    void draw(int _x, int _y, const string& text = "", int fontSize = 16, int borderThickness = 0,
              SDL_Color boxColor = {0, 0, 0, 0}, SDL_Color borderColor = {0, 0, 0, 0},
              SDL_Color textColor = {0, 0, 0, 0}, bool destroyable = true, SDL_Texture* texture = nullptr)
    {
        x = _x;
        y = _y;
        if (!isDestroyed)
        {
            graphics.draw_rect(x - w / 2, y - h / 2, w, h, borderThickness, boxColor, borderColor);
            if (texture != nullptr)
                graphics.render_center_of_texture(texture, x, y, w, h);
            if (!text.empty())
            {
                TTF_SizeText(graphics.PrStart, text.c_str(), &textWidth, &textHeight);
                graphics.draw_center_of_text(text.c_str(), fontSize, textColor, x, y);
            }
        }
    }

    void draw_default_offset(int _x, int _y, const string& text = "", int fontSize = 16,
                             int borderThickness = 0, SDL_Color boxColor = {0, 0, 0, 0},
                             SDL_Color borderColor = {0, 0, 0, 0}, SDL_Color textColor = {0, 0, 0, 0},
                             bool destroyable = true, SDL_Texture* texture = nullptr, double icon_scale = 0.666)
    {
        x = _x;
        y = _y;
        if (!isDestroyed)
        {
            graphics.draw_rect(x, y, w, h, borderThickness, boxColor, borderColor);
            if (texture != nullptr)
            {
                int imgW = w * icon_scale, imgH = h * icon_scale;
                graphics.render_center_of_texture(texture, x + w / 2, y + h / 2, imgW, imgH,
                                                  flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
            }
            if (!text.empty())
            {
                TTF_SizeText(graphics.PrStart, text.c_str(), &textWidth, &textHeight);
                graphics.draw_text(text.c_str(), fontSize, textColor, x + 10, y + h / 2 - textHeight / 3);
            }
        }
    }
};

#endif // FHI_Flower_Harvesting_Inc_BUTTON_H
