#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include "defs.h"

using namespace std;

void logErrorAndExit(const char *msg, const char *error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *PrStart;

    void init() {
        TTF_Init();
        PrStart = TTF_OpenFont("assets/font/pressStart.ttf", 24);
        TTF_SetFontHinting(PrStart, TTF_HINTING_NORMAL);
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ||
            !(window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) || !IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) ||
            !(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
            logErrorAndExit("Initialization Error", SDL_GetError());
        }
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_Log("Graphic init successful");
    }

    void prepareScene() const {
        SDL_SetRenderDrawColor(renderer, BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A);
        SDL_RenderClear(renderer);
    }

    void presentScene() const {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename) const {
        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (!texture) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
            return nullptr;
        }
        return texture;
    }

    void drawRect(int x, int y, int width, int height, int borderThickness = 0, SDL_Color color = {0, 0, 0, 0},
                  SDL_Color borderColor = {0, 0, 0, 0}, string name = "") const {
        if (borderThickness > 0) {
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_Rect border = {
                x - borderThickness, y - borderThickness, width + borderThickness * 2, height + borderThickness * 2
            };
            SDL_RenderFillRect(renderer, &border);
        }
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Rect rect = {x, y, width, height};
        SDL_RenderFillRect(renderer, &rect);
    }

    void drawCenterOfRect(int x, int y, int width, int height, int borderThickness = 0, SDL_Color color = {0, 0, 0, 0},
                          SDL_Color borderColor = {0, 0, 0, 0}) const {
        if (borderThickness > 0) {
            SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
            SDL_Rect border = {
                x - borderThickness - width / 2, y - borderThickness - height / 2, width + borderThickness * 2,
                height + borderThickness * 2
            };
            SDL_RenderFillRect(renderer, &border);
        }
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Rect rect = {x - width / 2, y - height / 2, width, height};
        SDL_RenderFillRect(renderer, &rect);
    }

    void renderTexture(SDL_Texture *texture, int x, int y, int width, int height,
                       SDL_RendererFlip flip = SDL_FLIP_NONE) const {
        SDL_Rect dest = {x, y, width, height};
        SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0, nullptr, flip);
    }

    void renderCenterOfTexture(SDL_Texture *texture, int x, int y, int width, int height,
                               SDL_RendererFlip flip = SDL_FLIP_NONE) const {
        SDL_Rect dest = {x - width / 2, y - height / 2, width, height};
        SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0, nullptr, flip);
    }

    void drawText(const char *text, int fontSize = 16, SDL_Color color = {0, 0, 0, 0}, int x = 0, int y = 0) const {
        TTF_Font *font = TTF_OpenFont("assets/font/pressStart.ttf", fontSize);
        SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect dest = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, nullptr, &dest);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }

    void drawCenterOfText(const char *text, int fontSize = 16, SDL_Color color = {0, 0, 0, 0}, int x = 0,
                          int y = 0) const {
        TTF_Font *font = TTF_OpenFont("assets/font/pressStart.ttf", fontSize);
        SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect dest = {x - surface->w / 2, y - surface->h / 2, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, nullptr, &dest);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }

    void quit() const {
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

#endif // _GRAPHICS__H
