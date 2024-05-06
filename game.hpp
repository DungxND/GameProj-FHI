#ifndef SAI___SCORE_ACCUMULATING_INCREMENTAL_GAME_H
#define SAI___SCORE_ACCUMULATING_INCREMENTAL_GAME_H

#include <SDL.h>
#include "graphics_n_audio.hpp"
#include "input.hpp"
#include "saver.hpp"
#include "components/button.hpp"

using namespace std;

struct Game
{
    Graphics graphics{};
    Saver saver;
    Input input;
    Painter painter;
    Button startButton, perkStat, scoreStat, scoreBoxButton, inactiveScoreBoxButton, upgradeTabMenu, perkMenu,
           settingTabMenu, sellBtn, timeUpgradeInfo, timeUpgradeBtn, valueUpgradeInfo, valueUpgradeBtn, xpStat,
           limitUpgradeInfo, limitUpgradeBtn;
    Button musicBtn;
    Mix_Music* musicx = nullptr;
    GameData gameData;
    uint32_t startTime, currTime{}, lastSameTime = 0;
    bool running = true;
    bool oldTimeSet = false;
    bool musicPlayed = false, musicPaused = false;
    int oldTime = 0;
    int boxSpawnTime = 0;
    int const SW = SCREEN_WIDTH, SH = SCREEN_HEIGHT;
    SDL_Texture *upgrade_icon, *perk_icon, *setting_icon, *ApScore;

    Game();

    void run();

    void draw_n_handle_elements();

    void draw_mainboard();

    void draw_respawn_timer();

    void draw_sideboard();

    void draw_upgrade_tab();

    void draw_perk_tab();

    void draw_setting_tab();

    void draw_stats();

    void music_init();

    void timer();

    void saveGame();

    void checkIfEsc();
};


#endif // SAI___SCORE_ACCUMULATING_INCREMENTAL_GAME_H
