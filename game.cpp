#include "game.hpp"

Game::Game() : input(&saver, &gameData)
{
    graphics.init();
    startTime = SDL_GetTicks64();
    saver.load_data(&gameData);
    startButton = Button(graphics, input, 200, 100);
    perkStat = scoreStat = Button(graphics, input, 200, 50);
    flowerButton = inactiveButton = Button(graphics, input, MAINBOARD_WIDTH / 12.5, MAINBOARD_HEIGHT / 12.5);
    upgradeTabMenu = perkMenu = settingTabMenu =
        Button(graphics, input, SIDEBOARD_WIDTH * 0.25, SIDEBOARD_HEIGHT * 0.1);
    timeUpgradeInfo = valueUpgradeInfo = limitUpgradeInfo = Button(graphics, input, SW * 0.27,
                                                                   SH * 0.16);
    timeUpgradeBtn = valueUpgradeBtn = limitUpgradeBtn = Button(graphics, input, SW * 0.27,
                                                                SH * 0.07);
    musicBtn = Button(graphics, input, SW * 0.27,
                      SH * 0.10);

    background = graphics.load_texture("assets/img/bg.png");
    valueUpgrader = Upgrader(graphics, input, 300, 100, "Value Upgrade", "Value of each flower",
                             gameData.calc_flower_upgrade_cost(), gameData.calc_flower_value(),
                             gameData.flowerValueUpgrade[0], gameData.calc_next_flower_value(),
                             gameData.flowerValueUpgrade[1]);
    ApScore = graphics.load_texture("assets/img/ApScore.png");
    upgradeIcon = graphics.load_texture("assets/img/upgrade.png");
    perkIcon = graphics.load_texture("assets/img/perk.png");
    flowerIcon = graphics.load_texture("assets/img/flower.png");
    settingIcon = graphics.load_texture("assets/img/gearIcon.png");
    musicx = graphics.load_music("assets/audio/ms1.mp3");
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
        draw_garden();
        draw_respawn_timer();
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

void Game::draw_respawn_timer()
{
    (currTime - gameData.lastSpawnTime - gameData.calc_spawn_time() > 0.0)
        ? boxSpawnTime = 0
        : boxSpawnTime = gameData.calc_spawn_time() - (currTime - gameData.lastSpawnTime);
    string respawnTimeStr = "Respawn Time: " + to_string(boxSpawnTime) + "ms";
    graphics.draw_text(respawnTimeStr.c_str(), 12, painter.white, SW * 0.04,
                       SH * 0.97);
    int boxHeight;

    graphics.draw_rect(SW * 0.1, SH * 0.53, 40, SH * 0.4, 5, painter.lightGrey,
                       painter.white);
    boxSpawnTime == 0
        ? boxHeight = SH * 0.4
        : boxHeight = SH * 0.4 * (1 - boxSpawnTime / gameData.calc_spawn_time());

    graphics.draw_rect(SW * 0.1, SH * 0.93 - boxHeight,
                       40, boxHeight,
                       3, painter.green, painter.white);
}

void Game::draw_sideboard()
{
    graphics.draw_rect(SW * 0.7, 0, SIDEBOARD_WIDTH, SIDEBOARD_HEIGHT, 3, painter.lightBrown,
                       painter.brown, "Side Board");
    upgradeTabMenu.draw_default_offset(SW * (0.7) + 15, SH * 0.88, "", 0, 3,
                                       painter.brown, painter.black, painter.white, false, upgradeIcon, 0.8);
    upgradeTabMenu.handle_tab_click(gameData, 1);
    perkMenu.draw_default_offset(SW * (0.7 + 0.3 * 1 / 3) + 15, SH * 0.88, "", 0,
                                 3, painter.brown, painter.black, painter.white, false, perkIcon, 0.8);
    perkMenu.handle_tab_click(gameData, 2);
    settingTabMenu.draw_default_offset(SW * (0.7 + 0.3 * 2 / 3) + 15, SH * 0.88, "", 0,
                                       3, painter.brown, painter.black, painter.white, false, settingIcon, 0.8);
    settingTabMenu.handle_tab_click(gameData, 3);
    switch (gameData.openingTab)
    {
    case 1:
        draw_upgrade_tab();
        break;
    case 2:
        draw_perk_tab();
        break;
    case 3:
        draw_setting_tab();
        break;
    default:
        SDL_Log("Out of range");
    }
}

void Game::draw_upgrade_tab()
{
    upgradeTabMenu.draw_default_offset(SW * (0.7) + 15, SH * 0.88, "", 0, 3,
                                       painter.darkBrown, painter.black, painter.white, false, upgradeIcon, 0.7);
    graphics.draw_center_of_text("Upgrade Menu", 25, painter.white, SW * 0.85, SH * 0.05);
    graphics.draw_rect(SW * 0.73, SH * 0.08, SW * 0.24, SH * 0.005, 0,
                       painter.white, painter.darkBrown, "line");
    /***** VALUE UPGRADE *****/
    valueUpgradeInfo.draw_upgrade_info(SW * 0.715, SH * 0.13, 16,
                                       "Value Upgrade", to_string(gameData.calc_flower_value()),
                                       to_string(gameData.calc_next_flower_value()));
    SDL_Color VUColor = (gameData.score >= gameData.calc_flower_upgrade_cost())
                            ? painter.lightGrey
                            : painter.grey;
    valueUpgradeBtn.draw_default_offset(SW * 0.715, valueUpgradeInfo.y + valueUpgradeInfo.h,
                                        "Cost: " + to_string(gameData.calc_flower_upgrade_cost()) + "$", 16, 3,
                                        VUColor,
                                        painter.darkBrown, painter.black);
    valueUpgradeBtn.handle_upgrade_click(gameData.flowerValueUpgrade, gameData.score,
                                         gameData.calc_flower_upgrade_cost());
    /***** SPAWN TIME UPGRADE *****/
    timeUpgradeInfo.draw_upgrade_info(SW * 0.715, SH * 0.4, 16,
                                      "Spawn Time Upgrade",
                                      to_string(static_cast<int>(gameData.calc_spawn_time())) + "ms",
                                      to_string(static_cast<int>(gameData.calc_next_spawn_time())) + "ms");
    SDL_Color STUColor = (gameData.score >= gameData.calc_spawn_time_upgrade_cost())
                             ? painter.lightGrey
                             : painter.grey;
    timeUpgradeBtn.draw_default_offset(SW * 0.715, timeUpgradeInfo.y + timeUpgradeInfo.h,
                                       "Cost: " + to_string(gameData.calc_spawn_time_upgrade_cost()) + "$", 16, 3,
                                       STUColor,
                                       painter.darkBrown, painter.black, false);
    timeUpgradeBtn.handle_upgrade_click(gameData.flowerSpawnTimeUpgrade, gameData.score,
                                        gameData.calc_spawn_time_upgrade_cost());
    valueUpgrader.draw_upgrade_icon(flowerIcon, 2, SW * 0.75, 100, 100);
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
    limitUpgradeInfo.draw_upgrade_info(SW * 0.715, SH * 0.13, 16,
                                       "Limit Upgrade", to_string(gameData.flowerLimitUpgrade[0]),
                                       to_string(gameData.flowerLimitUpgrade[0] + 1));
    SDL_Color LUColor = gameData.perk >= 1
                            ? painter.lightGrey
                            : painter.grey;
    valueUpgradeBtn.draw_default_offset(SW * 0.715, valueUpgradeInfo.y + valueUpgradeInfo.h,
                                        "Cost: " + to_string(1) + " Perk", 16, 3,
                                        LUColor,
                                        painter.darkBrown, painter.black);
    valueUpgradeBtn.handle_upgrade_click(gameData.flowerLimitUpgrade, gameData.perk, 1);
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

    // graphics.play_music()
}

void Game::draw_stats()
{
    perkStat.draw(SW * 0.61, SH * 0.05, "Perk: " + to_string(gameData.perk), 12,
                  5, painter.grey, painter.cyan, painter.white, false);
    scoreStat.draw(SW * 0.61 - SW * 0.17, SH * 0.05,
                   "Score: " + to_string(gameData.score), 12, 5, painter.grey, painter.green, painter.white, false);
    /** Limit **/
    string limit_str = "Flower: " + to_string(gameData.availableFlower) + '/' + to_string(
        gameData.flowerLimitUpgrade[0]);
    graphics.draw_text(limit_str.c_str(), 13, painter.white, SW * 0.5, SH * 0.97);
    /***** XP BAR *****/
    int xpNeeded = gameData.xp_to_next_level();
    graphics.draw_rect(SW * 0.025, SH * 0.019, SW * 0.3, SH * 0.065, 2, painter.grey, painter.white, "XP Bar");
    double xp_progess = static_cast<double>(gameData.xp) / xpNeeded;
    double xpBarWidth = SW * 0.29 * xp_progess;
    graphics.draw_rect(SW * 0.03, SH * 0.026, xpBarWidth, SH * 0.055, 0, painter.blue);
    string xp_str = "XP: " + to_string(gameData.xp) + "/" + to_string(xpNeeded);
    graphics.draw_center_of_text(xp_str.c_str(), 16, painter.white, SW * 0.15, SH * 0.05);
    /***** Tier Box *****/
    graphics.draw_rect(SW * 0.01, SH * 0.15, SW * 0.115, SH * 0.21, 2, painter.lightGrey, painter.white, "Tier Box");
}

void Game::music_init()
{
    if (gameData.musicPlaying && !musicPlayed && !musicPaused)
    {
        graphics.play_music(musicx, true);
        Mix_Volume(-1, gameData.musicVolume);
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
    if (static_cast<int>(gameData.playTime) % 30 == 0 && gameData.playTime != 0 && gameData.playTime != lastSameTime
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

// void Game::draw_xp_bar()
// {
//     graphics.draw_rect(SW * 0.7, SH * 0.05, SW * 0.3, SH * 0.02, 0,
//                       painter.lightGrey, painter.white, "XP Bar");
//     int xpBarWidth = SW * 0.3 * (gameData.xp - gameData.xpToLevelUp[gameData.level - 1])
//         / (gameData.xpToLevelUp[gameData.level] - gameData.xpToLevelUp[gameData.level - 1]);
//     graphics.draw_rect(SW * 0.7, SH * 0.05, xpBarWidth, SH * 0.02, 0, painter.green,
//                       painter.white);
//     graphics.draw_text(to_string(gameData.xp).c_str(), 12, painter.white, SW * 0.7 + 10,
//                       SH * 0.05 + 5);
//     graphics.draw_text(to_string(gameData.xpToLevelUp[gameData.level]).c_str(), 12, painter.white,
//                       SW * 0.7 + SW * 0.3 - 30, SH * 0.05 + 5);
// }
