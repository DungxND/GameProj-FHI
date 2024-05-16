#ifndef FHI_Flower_Harvesting_Inc_GAME_H
#define FHI_Flower_Harvesting_Inc_GAME_H

#include <SDL.h>
#include "graphics_n_audio.hpp"
#include "input.hpp"
#include "saver.hpp"
#include "components/button.hpp"
#include "components/upgrader.hpp"

using namespace std;

struct Game
{
    Graphics graphics{};
    Saver saver;
    Input input;
    Painter painter;
    Button startButton, perkStat, flowerStat, flowerButton, inactiveButton, normalUpgradeTabMenu, perkMenu,
           settingTabMenu, sellBtn, timeUpgradeInfo, timeUpgradeBtn, valueUpgradeInfo, valueUpgradeBtn, xpStat,
           limitUpgradeInfo, limitUpgradeBtn;

    Upgrader valueUpgrader, timeUpgrader, flowerLimitUpgrader;
    Button musicBtn, nextSongBtn, prevSongBtn, musicVolumeBtn;
    Button gardenMapBtn, prestigeMapBtn;
    Mix_Music *MM_CTDB = nullptr, *MM_MXLLLH = nullptr, *MM_HVCLHN = nullptr, *MM_IDLE = nullptr, *music = nullptr;;
    GameData gameData;
    uint32_t startTime, currTime{}, lastSameTime = 0;
    // currentMap 0=garden, 1=prestige
    int currentMap = 0, prevSongSelection = 0;
    bool running = true;
    bool oldTimeSet = false;
    bool musicPlayed = false, musicPaused = false;
    int oldTime = 0;
    int boxSpawnTime = 0, boxHeight = 0;
    int const SW = SCREEN_WIDTH, SH = SCREEN_HEIGHT;
    string currSongName;
    SDL_Texture *background, *upgradeIcon, *perkIcon, *settingIcon, *flowerIcon, *clockIcon, *manyFlowersIcon, *
                prestigeIcon, *slimArrowIcon;

    Game();

    void run();

    void draw_n_handle_elements();

    void draw_map_menu();

    void draw_garden();

    void draw_prestige_map();

    void draw_respawn_timer();

    void draw_sideboard();

    void draw_normal_upgrade_tab();

    void draw_prestige_upgrade_tab();

    void draw_perk_tab();

    void draw_setting_tab();

    void draw_stats();

    void music_init();

    void timer();

    void saveGame();

    void checkIfEsc();
};


#endif // FHI_Flower_Harvesting_Inc_GAME_H
