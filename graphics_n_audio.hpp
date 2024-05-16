#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include "defs.hpp"

using namespace std;

void logErrorAndExit(const char* msg, const char* error);

struct Graphics
{
    SDL_Renderer* renderer;
    SDL_Window* window;
    TTF_Font* PrStart;

    // 0=none, 1=flower upgrade, 2=perk upgrade, 3=prestige upgrade
    int aBoardOpenedInMenu = 0;

    void init();

    void prepare_scene() const;

    void presentScene() const { SDL_RenderPresent(renderer); }

    SDL_Texture* load_texture(const char* filename) const;

    void draw_rect(int x, int y, int width, int height, int borderThickness = 0, SDL_Color color = {0, 0, 0, 0},
                   SDL_Color borderColor = {0, 0, 0, 0}, const string& name = "") const;

    void draw_center_of_rect(int x, int y, int width, int height, int borderThickness = 0,
                             SDL_Color color = {0, 0, 0, 0},
                             SDL_Color borderColor = {0, 0, 0, 0}) const;

    void render_texture(SDL_Texture* texture, int x, int y, int width, int height,
                        SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    void render_center_of_texture(SDL_Texture* texture, int x, int y, int width, int height,
                                  SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    void draw_text(const char* text, int fontSize = 16, SDL_Color color = {0, 0, 0, 0}, int x = 0, int y = 0) const;

    void draw_center_of_text(const char* text, int fontSize = 16, SDL_Color color = {0, 0, 0, 0}, int x = 0,
                             int y = 0) const;

    Mix_Music* load_music(const char* filename) const;

    void play_music(Mix_Music* music, bool loop = true);

    void change_music(Mix_Music* music);

    void quit() const;
};


#endif // _GRAPHICS__H
