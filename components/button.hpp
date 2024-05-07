#ifndef SAI___SCORE_ACCUMULATING_INCREMENTAL_BUTTON_H
#define SAI___SCORE_ACCUMULATING_INCREMENTAL_BUTTON_H

#include <string>
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
    bool upgradeInfoOpening = false;
    string name;

    Button() = default;

    explicit Button(Graphics& graphics, Input& input, int w = 300, int h = 100, string name = "")
    {
        this->graphics = graphics;
        this->input = &input;
        this->w = w;
        this->h = h;
        this->name = move(name);
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
            if (gameData.musicPlaying && !musicPaused)
            {
                gameData.musicPlaying = false;
                Mix_PauseMusic();
                musicPaused = true;
                SDL_Log("Music paused");
            }
            else
            {
                gameData.musicPlaying = true;
                Mix_ResumeMusic();
                musicPaused = false;
                SDL_Log("resumed music");
            }
            isClicked = true;
        }
        if (!input->mouse_clicked)
        {
            isClicked = false;
        }
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
                graphics.render_center_of_texture(texture, x + w / 2, y + h / 2, imgW, imgH);
            }
            if (!text.empty())
            {
                TTF_SizeText(graphics.PrStart, text.c_str(), &textWidth, &textHeight);
                graphics.draw_text(text.c_str(), fontSize, textColor, x + 10, y + h / 2 - textHeight / 3);
            }
        }
    }

    void draw_upgrade_info(int _x, int _y, int fontSize = 16,
                           const string& upgradeTitle = "", const string& currentValue = "",
                           const string& nextValue = "")
    {
        x = _x;
        y = _y;
        int borderThickness = 3;
        graphics.draw_rect(x, y, w, h, borderThickness,
                           painter.brown, painter.darkBrown, upgradeTitle);
        graphics.draw_text(upgradeTitle.c_str(), 18, painter.white, x + 20, y + 20);
        string currentScoreValue = "Current value: " + currentValue;
        graphics.draw_text(currentScoreValue.c_str(), 14, painter.lightGrey, x + 20, y + 60);
        string nextScoreValue = "Next value: " + nextValue;
        graphics.draw_text(nextScoreValue.c_str(), 14, painter.lightGrey, x + 20, y + 85);
    }

    void handle_open_upgrade_info_click()
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h)
        {
            upgradeInfoOpening = true;
        }
    }

    void handle_close_upgrade_info_click()
    {
        mouseX = input->mouse_x;
        mouseY = input->mouse_y;
        if (input->mouse_clicked && mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h)
        {
            upgradeInfoOpening = false;
        }
    }
};

#endif // SAI___SCORE_ACCUMULATING_INCREMENTAL_BUTTON_H
