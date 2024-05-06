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

    void init();

    void prepareScene() const;

    void presentScene() const { SDL_RenderPresent(renderer); }

    SDL_Texture* loadTexture(const char* filename) const;

    void drawRect(int x, int y, int width, int height, int borderThickness = 0, SDL_Color color = {0, 0, 0, 0},
                  SDL_Color borderColor = {0, 0, 0, 0}, const string& name = "") const;

    void drawCenterOfRect(int x, int y, int width, int height, int borderThickness = 0, SDL_Color color = {0, 0, 0, 0},
                          SDL_Color borderColor = {0, 0, 0, 0}) const;

    void renderTexture(SDL_Texture* texture, int x, int y, int width, int height,
                       SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    void renderCenterOfTexture(SDL_Texture* texture, int x, int y, int width, int height,
                               SDL_RendererFlip flip = SDL_FLIP_NONE) const;

    void drawText(const char* text, int fontSize = 16, SDL_Color color = {0, 0, 0, 0}, int x = 0, int y = 0) const;

    void drawCenterOfText(const char* text, int fontSize = 16, SDL_Color color = {0, 0, 0, 0}, int x = 0,
                          int y = 0) const;

    Mix_Music* loadMusic(const char* filename) const;

    void playMusic(Mix_Music* music, bool loop = true);

    void quit() const;
};

#endif // _GRAPHICS__H
