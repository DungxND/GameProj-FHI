#include "game.hpp"

Game::Game()
    : input(&saver, &gameData)
{
    graphics.init();
    startTime = SDL_GetTicks64();
    saver.load_data(&gameData);
    startButton = Button(graphics, input, 200, 100);
    perkStat = flowerStat = Button(graphics, input, 200, 50);
    flowerButton = inactiveButton = Button(graphics, input, MAINBOARD_WIDTH / 12.5, MAINBOARD_HEIGHT / 12.5);
    normalUpgradeTabMenu = perkMenu = settingTabMenu =
        Button(graphics, input, SIDEBOARD_WIDTH * 0.25, SIDEBOARD_HEIGHT * 0.1);
    musicBtn = Button(graphics, input, SW * 0.27,
                      SH * 0.10);
    musicVolumeBtn = Button(graphics, input, SW * 0.27,
                            SH * 0.06);
    background = graphics.load_texture("assets/img/bg.png");
    upgradeIcon = graphics.load_texture("assets/img/upgrade.png");
    perkIcon = graphics.load_texture("assets/img/perk.png");
    flowerIcon = graphics.load_texture("assets/img/flower.png");
    clockIcon = graphics.load_texture("assets/img/clock.png");
    settingIcon = graphics.load_texture("assets/img/gearIcon.png");
    manyFlowersIcon = graphics.load_texture("assets/img/manyflw.png");
    prestigeIcon = graphics.load_texture("assets/img/prestige.png");
    slimArrowIcon = graphics.load_texture("assets/img/slimArrow.png");
    MM_CTDB = graphics.load_music("assets/audio/CTDB.mp3");
    MM_HVCLHN = graphics.load_music("assets/audio/HVCLHN.mp3");
    MM_MXLLLH = graphics.load_music("assets/audio/MXLLLH.mp3");
    MM_IDLE = graphics.load_music("assets/audio/BBG.mp3");
    valueUpgrader = Upgrader(graphics, input, 115, SW * 0.74, 100, "Value Upgrade", "Flowers", "Value of each flower",
                             gameData.flowerValueUpgrade[1], 1);
    timeUpgrader = Upgrader(graphics, input, 115, SW * 0.87, 100, "Spawn Time Upgrade", "Flowers",
                            "Delay time between flower spawn",
                            gameData.flowerSpawnTimeUpgrade[1], 1);
    flowerLimitUpgrader = Upgrader(graphics, input, 115, SW * 0.74, 100, "Limit Upgrade", "Perks",
                                   "Maximum flowers in the garden",
                                   gameData.flowerLimitUpgrade[1], 2);
    prevSongBtn = Button(graphics, input, 40, 80);
    nextSongBtn = Button(graphics, input, 40, 80, "", true);
    gardenMapBtn = prestigeMapBtn = Button(graphics, input, 90, 80);
    prevSongSelection = gameData.musicSelection;
}

void Game::run()
{
    while (running)
    {
        timer();
        graphics.prepare_scene();
        checkIfEsc();
        draw_n_handle_elements();
        input.get();
        graphics.presentScene();
        saveGame();
    }
    saveGame();
    gameData.isFirstRun = false;
    graphics.quit();
}

void Game::draw_n_handle_elements()
{
    if (startButton.isDestroyed)
    {
        draw_map_menu();
        switch (currentMap)
        {
        case 1:
            draw_prestige_map();
            break;
        default:
            draw_garden();
            draw_respawn_timer();
        }
        draw_sideboard();
        draw_stats();
        music_init();
        // draw_xp_bar();
    }
    else
    {
        graphics.render_texture(background, 0, 0,SCREEN_WIDTH,SCREEN_HEIGHT);
        graphics.draw_center_of_text("FHI - Flower Harvesting Incremental", 33, painter.white, SW / 2,
                                     SH / 2 - 200);
        startButton.draw(SW / 2, SH / 2 + 50, "Start", 18, 5, painter.black, painter.red,
                         painter.white, true);
        startButton.handle_click(gameData);
    }
    graphics.draw_rect(input.mouse_x, input.mouse_y, 7, 7, 1, painter.yellow, painter.grey);
}

void Game::draw_map_menu()
{
    SDL_Color gardenBtnBGColor = painter.brown;
    SDL_Color prestigeBtnBGColor = painter.brown;
    if (currentMap == 0)
    {
        gardenBtnBGColor = painter.darkBrown;
    }
    else
    {
        prestigeBtnBGColor = painter.darkBrown;
    }
    gardenMapBtn.draw_default_offset(SW * 0.2, SH - gardenMapBtn.h + 1, "", 0, 3, gardenBtnBGColor, painter.black,
                                     painter.white, false, flowerIcon, 0.7);
    gardenMapBtn.handle_map_click(currentMap, 0);
    prestigeMapBtn.draw_default_offset(SW * 0.3, SH - gardenMapBtn.h + 1, "", 0, 3, prestigeBtnBGColor, painter.black,
                                       painter.white, false, prestigeIcon, 0.7);
    prestigeMapBtn.handle_map_click(currentMap, 1);
}

void Game::draw_garden()
{
    graphics.draw_rect(SW * 0.20, SH * 0.19, SW * 0.45, SH * 0.66, 5,
                       painter.darkBrown, painter.brown, "Main Board");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (gameData.flowerArr[i][j])
            {
                Button tempBtn = flowerButton;
                tempBtn.draw_default_offset(SW * 0.21 + i * MAINBOARD_WIDTH / 11.5,
                                            SH * 0.21 + j * MAINBOARD_HEIGHT / 11.5 + 5, "", 1, 2,
                                            painter.lightGreen, painter.black);
                tempBtn.handle_default_offset_click(gameData, true, i, j);
            }
            else
            {
                Button tempunBtn = inactiveButton;
                tempunBtn.draw_default_offset(SW * 0.21 + i * MAINBOARD_WIDTH / 11.5,
                                              SH * 0.21 + j * MAINBOARD_HEIGHT / 11.5, "", 1, 2,
                                              painter.lightBrown, painter.black);
            }
        }
    }
    gameData.randomize_flower_spawn(currTime);
}

void Game::draw_prestige_map()
{
}

void Game::draw_respawn_timer()
{
    (currTime - gameData.lastSpawnTime - gameData.calc_spawn_time() > 0.0)
        ? boxSpawnTime = 0
        : boxSpawnTime = gameData.calc_spawn_time() - (currTime - gameData.lastSpawnTime);
    string respawnTimeStr = "Respawn Time: " + to_string(boxSpawnTime) + "ms";
    graphics.draw_text(respawnTimeStr.c_str(), 12, painter.white, SW * 0.01,
                       SH * 0.97);

    graphics.draw_rect(SW * 0.16, SH * 0.45, 40, SH * 0.4, 5, painter.lightGrey,
                       painter.white);
    boxSpawnTime == 0
        ? boxHeight = SH * 0.4
        : boxHeight = SH * 0.4 * (1 - boxSpawnTime / gameData.calc_spawn_time());

    graphics.draw_rect(SW * 0.16, SH * 0.85 - boxHeight,
                       40, boxHeight,
                       3, painter.green, painter.white);
}

void Game::draw_sideboard()
{
    graphics.draw_rect(SW * 0.7, 0, SIDEBOARD_WIDTH, SIDEBOARD_HEIGHT, 3, painter.lightBrown,
                       painter.brown, "Side Board");
    if (currentMap == 0)
    {
        normalUpgradeTabMenu.draw_default_offset(SW * (0.7) + 15, SH * 0.88, "", 0, 3,
                                                 painter.brown, painter.black, painter.white, false, upgradeIcon, 0.8);
        normalUpgradeTabMenu.handle_tab_click(gameData, 1);
    }
    perkMenu.draw_default_offset(SW * (0.7 + 0.3 * 1 / 3) + 15, SH * 0.88, "", 0,
                                 3, painter.brown, painter.black, painter.white, false, perkIcon, 0.8);
    perkMenu.handle_tab_click(gameData, 2);
    settingTabMenu.draw_default_offset(SW * (0.7 + 0.3 * 2 / 3) + 15, SH * 0.88, "", 0,
                                       3, painter.brown, painter.black, painter.white, false, settingIcon, 0.8);
    settingTabMenu.handle_tab_click(gameData, 3);
    switch (gameData.openingTab)
    {
    default:
        if (currentMap == 0)
            draw_normal_upgrade_tab();
        else if (currentMap == 1)
            draw_prestige_upgrade_tab();
        break;
    case 2:
        draw_perk_tab();
        break;
    case 3:
        draw_setting_tab();
        break;
    }
}

void Game::draw_normal_upgrade_tab()
{
    normalUpgradeTabMenu.draw_default_offset(SW * (0.7) + 15, SH * 0.88, "", 0, 3,
                                             painter.darkBrown, painter.black, painter.white, false, upgradeIcon, 0.7);
    graphics.draw_center_of_text("Upgrade Menu", 25, painter.white, SW * 0.85, SH * 0.05);
    graphics.draw_rect(SW * 0.73, SH * 0.08, SW * 0.24, SH * 0.005, 0,
                       painter.white, painter.darkBrown, "line");
    /***** VALUE UPGRADE *****/
    valueUpgrader.draw_upgrade_icon(flowerIcon, gameData.flower, gameData.flowerValueUpgrade[0],
                                    gameData.calc_flower_upgrade_cost(), gameData.calc_flower_value(),
                                    gameData.calc_next_flower_value());
    /***** SPAWN TIME UPGRADE *****/
    timeUpgrader.draw_upgrade_icon(clockIcon, gameData.flower, gameData.flowerSpawnTimeUpgrade[0],
                                   gameData.calc_spawn_time_upgrade_cost(), gameData.calc_spawn_time(),
                                   gameData.calc_next_spawn_time());
}

void Game::draw_prestige_upgrade_tab()
{
    graphics.draw_rect(SW * 0.15, SH * 0.2, SW * 0.5, SH * 0.5, 5, painter.darkBrown, painter.brown, "Prestige Board");
    graphics.draw_center_of_text("Reach level 11 to unlock Prestige", 18, painter.white, SW * 0.4, SH * 0.3);
}

void Game::draw_perk_tab()
{
    perkMenu.draw_default_offset(SW * (0.7 + 0.3 * 1 / 3) + 15, SH * 0.88, "", 0,
                                 3, painter.darkBrown, painter.black, painter.white, false, perkIcon, 0.7);
    graphics.draw_center_of_text("Perk Menu", 25, painter.white, SW * 0.85,
                                 SH * 0.05);
    graphics.draw_rect(SW * 0.73, SH * 0.08, SW * 0.24, SH * 0.005, 0,
                       painter.white, painter.darkBrown, "line");
    /*** Limit Upgrade***/
    flowerLimitUpgrader.draw_upgrade_icon(manyFlowersIcon, gameData.perk, gameData.flowerLimitUpgrade[0],
                                          1, gameData.flowerLimitUpgrade[0],
                                          gameData.flowerLimitUpgrade[0] + 1);
}

void Game::draw_setting_tab()
{
    settingTabMenu.draw_default_offset(SW * (0.7 + 0.3 * 2 / 3) + 15,
                                       SH * 0.88, "", 0, 3, painter.darkBrown, painter.black,
                                       painter.white, false, settingIcon, 0.7);
    graphics.draw_center_of_text("Settings", 25, painter.white, SW * 0.85,
                                 SH * 0.05);
    graphics.draw_rect(SW * 0.73, SH * 0.08, SW * 0.24, SH * 0.005, 0,
                       painter.white, painter.darkBrown, "line");
    string playTimeStr = "Play Time: " + to_string(static_cast<int>(gameData.playTime)) + "s";
    graphics.draw_text(playTimeStr.c_str(), 12, painter.white, SW * 0.7 + 10,
                       SH * 0.83);

    /** Music **/
    if (musicPlayed && !musicPaused)
    {
        musicBtn.draw_default_offset(SW * 0.715, SH * 0.1, "Music: On", 16, 3,
                                     painter.lightGrey, painter.darkBrown, painter.black);
    }
    else
    {
        musicBtn.draw_default_offset(SW * 0.715, SH * 0.1, "Music: Off", 16, 3,
                                     painter.grey, painter.darkBrown, painter.black);
    }
    musicBtn.handle_music_click(gameData, musicPaused);
    int selection = gameData.musicSelection;

    switch (selection % 4)
    {
    case 1:
        music = MM_HVCLHN;
        currSongName = "Hat ve cay lua hom nay";
        break;
    case 2:
        music = MM_CTDB;
        currSongName = "Chien thang Dien Bien";
        break;
    case 3:
        music = MM_IDLE;
        currSongName = "BG Bardcore";
        break;
    default:
        music = MM_MXLLLH;
        currSongName = "Mua xuan lang lua lang hoa";
    }
    if (prevSongSelection != selection)
    {
        graphics.change_music(music);
        prevSongSelection = selection;
    }

    graphics.draw_center_of_text(currSongName.c_str(), 10, painter.white, SW * 0.85, SH * 0.27);
    nextSongBtn.draw_default_offset(SW * 0.715, SH * 0.22, "", 16, 3,
                                    painter.brown, painter.darkBrown, painter.white, false, slimArrowIcon, 1);
    nextSongBtn.handle_next_song_click(gameData);
    prevSongBtn.draw_default_offset(SW * 0.955, SH * 0.22, "", 16, 3,
                                    painter.brown, painter.darkBrown, painter.white, false, slimArrowIcon, 1);
    prevSongBtn.handle_prev_song_click(gameData);
    // Music Volume
    musicVolumeBtn.draw_default_offset(SW * 0.715, SH * 0.33,
                                       "", 16, 3,
                                       painter.lightBrown, painter.darkBrown, painter.white);
    musicVolumeBtn.handle_volume_slider(gameData);
    Mix_VolumeMusic(gameData.musicVolume);
}

void Game::draw_stats()
{
    perkStat.draw(SW * 0.61, SH * 0.05, "Perk: " + to_string(gameData.perk), 12,
                  5, painter.grey, painter.cyan, painter.white, false);
    flowerStat.draw(SW * 0.61 - SW * 0.17, SH * 0.05,
                    "Flower: " + to_string(gameData.flower), 12, 5, painter.grey, painter.green, painter.white, false);
    /** Limit **/
    string limit_str = "Flower: " + to_string(gameData.availableFlower) + '/' + to_string(
        gameData.flowerLimitUpgrade[0]);
    graphics.draw_text(limit_str.c_str(), 13, painter.white, SW * 0.5, SH * 0.97);
    /***** XP BAR *****/
    int xpNeeded = gameData.xp_to_next_level();
    graphics.draw_rect(SW * 0.025, SH * 0.019, SW * 0.25, SH * 0.065, 2, painter.grey, painter.white, "XP Bar");
    double xp_progess = static_cast<double>(gameData.xp) / xpNeeded;
    double xpBarWidth = SW * 0.24 * xp_progess;
    graphics.draw_rect(SW * 0.03, SH * 0.026, xpBarWidth, SH * 0.055, 0, painter.blue);
    string xp_str = "XP: " + to_string(gameData.xp) + "/" + to_string(xpNeeded);
    graphics.draw_center_of_text(xp_str.c_str(), 15, painter.white, SW * 0.15, SH * 0.05);
    graphics.draw_rect(SW * 0.275, SH * 0.019, SW * 0.05, SH * 0.065, 4, painter.lightBlue, painter.white, "Level Box");
    graphics.draw_center_of_text(to_string(gameData.level).c_str(), 18, painter.black, SW * 0.3, SH * 0.05);
    /***** Tier Box *****/
    graphics.draw_rect(SW * 0.01, SH * 0.15, SW * 0.115, SH * 0.21, 2, painter.darkGrey, painter.white, "Tier Box");
    graphics.draw_rect(SW * 0.01 + 3, SH * 0.15 + 3, SW * 0.115 - 6, SH * 0.21 - SH * 0.03, 0, painter.lightGreen);
    graphics.draw_center_of_text("Tier: Grass", 12, painter.white, SW * 0.06, SH * 0.35);
}

void Game::music_init()
{
    if (gameData.musicShouldPlay && !musicPlayed && !musicPaused)
    {
        switch (gameData.musicSelection % 4)
        {
        case 1:
            music = MM_HVCLHN;
            break;
        case 2:
            music = MM_CTDB;
            break;
        case 3:
            music = MM_IDLE;
            break;
        default:
            music = MM_MXLLLH;
        }
        graphics.play_music(music, true);
        Mix_VolumeMusic(gameData.musicVolume);
        musicPlayed = true;
        SDL_Log("Music Started...");
    }
}

void Game::timer()
{
    currTime = SDL_GetTicks64();
    if (!oldTimeSet)
    {
        oldTime = static_cast<int>(gameData.playTime);
        SDL_Log("Old time: %d", oldTime);
        oldTimeSet = true;
    }
    gameData.playTime = (currTime - startTime) / 1000 + oldTime;
}

void Game::saveGame()
{
    if (static_cast<int>(gameData.playTime) % 10 == 0 && gameData.playTime != 0 && gameData.playTime != lastSameTime
        || !running)
    {
        saver.save_data(&gameData);
        lastSameTime = gameData.playTime;
    }
}

void Game::checkIfEsc()
{
    if (input.isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        running = false;
        SDL_Log("Exiting...");
        SDL_Delay(100);
    }
}

