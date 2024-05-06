#include "graphics_n_audio.hpp"


void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::init()
{
    TTF_Init();
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD);
    PrStart = TTF_OpenFont("assets/font/pressStart.ttf", 24);
    TTF_SetFontHinting(PrStart, TTF_HINTING_NORMAL);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ||
        !(window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) ||
        !IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) ||
        !(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
        || Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 2048) < 0)
    {
        logErrorAndExit("Initialization Error", SDL_GetError());
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetWindowIcon(window, IMG_Load("assets/img/icon.png"));
    SDL_Log("Graphic init successful");
}

void Graphics::prepareScene() const
{
    SDL_SetRenderDrawColor(renderer, BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, BG_COLOR_A);
    SDL_RenderClear(renderer);
}

SDL_Texture* Graphics::loadTexture(const char* filename) const
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
    if (!texture)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
        return nullptr;
    }
    return texture;
}

void Graphics::drawRect(int x, int y, int width, int height, int borderThickness, SDL_Color color,
                        SDL_Color borderColor, const string& name) const
{
    if (borderThickness > 0)
    {
        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_Rect border = {
            x - borderThickness, y - borderThickness, width + borderThickness * 2,
            height + borderThickness * 2
        };
        SDL_RenderFillRect(renderer, &border);
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
}

void Graphics::drawCenterOfRect(int x, int y, int width, int height, int borderThickness,
                                SDL_Color color,
                                SDL_Color borderColor) const
{
    if (borderThickness > 0)
    {
        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_Rect border = {
            x - borderThickness - width / 2, y - borderThickness - height / 2,
            width + borderThickness * 2, height + borderThickness * 2
        };
        SDL_RenderFillRect(renderer, &border);
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x - width / 2, y - height / 2, width, height};
    SDL_RenderFillRect(renderer, &rect);
}

void Graphics::renderTexture(SDL_Texture* texture, int x, int y, int width, int height,
                             SDL_RendererFlip flip) const
{
    SDL_Rect dest = {x, y, width, height};
    SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0, nullptr, flip);
}

void Graphics::renderCenterOfTexture(SDL_Texture* texture, int x, int y, int width, int height,
                                     SDL_RendererFlip flip) const
{
    SDL_Rect dest = {x - width / 2, y - height / 2, width, height};
    SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0, nullptr, flip);
}

void Graphics::drawText(const char* text, int fontSize, SDL_Color color, int x, int y) const
{
    TTF_SetFontSize(PrStart, fontSize);
    SDL_Surface* surface = TTF_RenderText_Solid(PrStart, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Graphics::drawCenterOfText(const char* text, int fontSize, SDL_Color color, int x,
                                int y) const
{
    TTF_SetFontSize(PrStart, fontSize);
    SDL_Surface* surface = TTF_RenderText_Solid(PrStart, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest = {x - surface->w / 2, y - surface->h / 2, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

Mix_Music* Graphics::loadMusic(const char* filename) const
{
    Mix_Music* music = Mix_LoadMUS(filename);
    if (!music)
    {
        SDL_Log("ERROR: %s", Mix_GetError());
        quit();
    }
    return music;
}

void Graphics::playMusic(Mix_Music* music, bool loop)
{
    int loops = (loop) ? -1 : 0;
    {
        Mix_PlayMusic(music, loops);
    }
}

void Graphics::quit() const
{
    IMG_Quit();
    TTF_CloseFont(PrStart);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}
