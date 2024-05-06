#include "game.hpp"

Game::Game() : input(&saver, &gameData)
{
    graphics.init();
    startTime = SDL_GetTicks();
    saver.load_data(&gameData);
    startButton = Button(graphics, input, 200, 100);
    perkStat = scoreStat = Button(graphics, input, 200, 50);
    scoreBoxButton = inactiveScoreBoxButton = Button(graphics, input, MAINBOARD_WIDTH / 10, MAINBOARD_HEIGHT / 10);
    upgradeTabMenu = perkMenu = settingTabMenu =
        Button(graphics, input, SIDEBOARD_WIDTH * 0.25, SIDEBOARD_HEIGHT * 0.1);
    timeUpgradeInfo = valueUpgradeInfo = limitUpgradeInfo = Button(graphics, input, SW * 0.27,
                                                                   SH * 0.16);
    timeUpgradeBtn = valueUpgradeBtn = limitUpgradeBtn = Button(graphics, input, SW * 0.27,
                                                                SH * 0.07);
    musicBtn = Button(graphics, input, SW * 0.27,
                      SH * 0.10);
    ApScore = graphics.loadTexture("assets/img/ApScore.png");
    upgrade_icon = graphics.loadTexture("assets/img/upgrade.png");
    perk_icon = graphics.loadTexture("assets/img/perk.png");
    setting_icon = graphics.loadTexture("assets/img/gearIcon.png");
    musicx = graphics.loadMusic("assets/audio/ms1.mp3");
}

void Game::run()
{
    while (running)
    {
        timer();
        graphics.prepareScene();
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
    startButton.draw(SW / 2, SH / 2 + 50, "Start", 18, 5, painter.black, painter.red,
                     painter.white, true);
    startButton.handleClick(gameData);
    if (startButton.isDestroyed)
    {
        draw_mainboard();
        draw_respawn_timer();
        draw_sideboard();
        draw_stats();
        music_init();
        // draw_xp_bar();
    }
    else
    {
        graphics.drawCenterOfText("SAI - Score Accumulating Incremental", 33, painter.white, SW / 2,
                                  SH / 2 - 200);
    }
    graphics.drawRect(input.mouse_x, input.mouse_y, 7, 7, 1, painter.yellow, painter.grey);
}

void Game::draw_mainboard()
{
    graphics.drawRect(SW * 0.14, SH * 0.175, SW * 0.52, SH * 0.77, 5,
                      painter.darkBrown, painter.brown, "Main Board");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (gameData.boxArr[i][j])
            {
                Button tempBtn = scoreBoxButton;
                tempBtn.drawDefaultOffset(SW * 0.15 + i * MAINBOARD_WIDTH / 10,
                                          SH * 0.2 + j * MAINBOARD_HEIGHT / 10 + 5, "", 1, 2,
                                          painter.lightGreen, painter.black);
                tempBtn.handleDefaultOffetClick(gameData, true, i, j);
            }
            else
            {
                Button tempunBtn = inactiveScoreBoxButton;
                tempunBtn.drawDefaultOffset(SW * 0.15 + i * MAINBOARD_WIDTH / 10,
                                            SH * 0.2 + j * MAINBOARD_HEIGHT / 10, "", 1, 2,
                                            painter.lightBrown, painter.black);
            }
        }
    }
    gameData.randomizeScoreBoxes(currTime);
}

void Game::draw_respawn_timer()
{
    (currTime - gameData.lastSpawnTime - gameData.calSpawnTime() > 0.0)
        ? boxSpawnTime = 0
        : boxSpawnTime = gameData.calSpawnTime() - (currTime - gameData.lastSpawnTime);
    string respawnTimeStr = "Respawn Time: " + to_string(boxSpawnTime) + "ms";
    graphics.drawText(respawnTimeStr.c_str(), 12, painter.white, SW * 0.04,
                      SH * 0.97);
    int boxHeight;

    graphics.drawRect(SW * 0.1, SH * 0.53, 40, SH * 0.4, 5, painter.lightGrey,
                      painter.white);
    boxSpawnTime == 0
        ? boxHeight = SH * 0.4
        : boxHeight = SH * 0.4 * (1 - boxSpawnTime / gameData.calSpawnTime());

    graphics.drawRect(SW * 0.1, SH * 0.93 - boxHeight,
                      40, boxHeight,
                      3, painter.green, painter.white);
}

void Game::draw_sideboard()
{
    graphics.drawRect(SW * 0.7, 0, SIDEBOARD_WIDTH, SIDEBOARD_HEIGHT, 3, painter.lightBrown,
                      painter.brown, "Side Board");
    upgradeTabMenu.drawDefaultOffset(SW * (0.7) + 15, SH * 0.88, "", 0, 3,
                                     painter.brown, painter.black, painter.white, false, upgrade_icon, 0.8);
    upgradeTabMenu.handleTabClick(gameData, 1);
    perkMenu.drawDefaultOffset(SW * (0.7 + 0.3 * 1 / 3) + 15, SH * 0.88, "", 0,
                               3, painter.brown, painter.black, painter.white, false, perk_icon, 0.8);
    perkMenu.handleTabClick(gameData, 2);
    settingTabMenu.drawDefaultOffset(SW * (0.7 + 0.3 * 2 / 3) + 15, SH * 0.88, "", 0,
                                     3, painter.brown, painter.black, painter.white, false, setting_icon, 0.8);
    settingTabMenu.handleTabClick(gameData, 3);
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
    upgradeTabMenu.drawDefaultOffset(SW * (0.7) + 15, SH * 0.88, "", 0, 3,
                                     painter.darkBrown, painter.black, painter.white, false, upgrade_icon, 0.7);
    graphics.drawCenterOfText("Upgrade Menu", 25, painter.white, SW * 0.85, SH * 0.05);
    graphics.drawRect(SW * 0.73, SH * 0.08, SW * 0.24, SH * 0.005, 0,
                      painter.white, painter.darkBrown, "line");
    /***** VALUE UPGRADE *****/
    valueUpgradeInfo.drawUpgradeInfo(SW * 0.715, SH * 0.13, 16,
                                     "Value Upgrade", to_string(gameData.calBoxValue()),
                                     to_string(gameData.calNextBoxValue()));
    SDL_Color VUColor = (gameData.score >= gameData.calBoxUpgradeCost())
                            ? painter.lightGrey
                            : painter.grey;
    valueUpgradeBtn.drawDefaultOffset(SW * 0.715, valueUpgradeInfo.y + valueUpgradeInfo.h,
                                      "Cost: " + to_string(gameData.calBoxUpgradeCost()) + "$", 16, 3,
                                      VUColor,
                                      painter.darkBrown, painter.black);
    valueUpgradeBtn.handleUpgradeClick(gameData.boxValueUpgrade, gameData.score, gameData.calBoxUpgradeCost());
    /***** SPAWN TIME UPGRADE *****/
    timeUpgradeInfo.drawUpgradeInfo(SW * 0.715, SH * 0.4, 16,
                                    "Spawn Time Upgrade",
                                    to_string(static_cast<int>(gameData.calSpawnTime())) + "ms",
                                    to_string(static_cast<int>(gameData.calNextSpawnTime())) + "ms");
    SDL_Color STUColor = (gameData.score >= gameData.calSpawnTimeUpgradeCost())
                             ? painter.lightGrey
                             : painter.grey;
    timeUpgradeBtn.drawDefaultOffset(SW * 0.715, timeUpgradeInfo.y + timeUpgradeInfo.h,
                                     "Cost: " + to_string(gameData.calSpawnTimeUpgradeCost()) + "$", 16, 3,
                                     STUColor,
                                     painter.darkBrown, painter.black, false);
    timeUpgradeBtn.handleUpgradeClick(gameData.boxSpawnTimeUprade, gameData.score,
                                      gameData.calSpawnTimeUpgradeCost());
}

void Game::draw_perk_tab()
{
    perkMenu.drawDefaultOffset(SW * (0.7 + 0.3 * 1 / 3) + 15, SH * 0.88, "", 0,
                               3, painter.darkBrown, painter.black, painter.white, false, perk_icon, 0.7);
    graphics.drawCenterOfText("Perk Menu", 25, painter.white, SW * 0.85,
                              SH * 0.05);
    graphics.drawRect(SW * 0.73, SH * 0.08, SW * 0.24, SH * 0.005, 0,
                      painter.white, painter.darkBrown, "line");
    /*** Limit Upgrade***/
    limitUpgradeInfo.drawUpgradeInfo(SW * 0.715, SH * 0.13, 16,
                                     "Limit Upgrade", to_string(gameData.boxLimitUpgrade[0]),
                                     to_string(gameData.boxLimitUpgrade[0] + 1));
    SDL_Color LUColor = gameData.perk >= 1
                            ? painter.lightGrey
                            : painter.grey;
    valueUpgradeBtn.drawDefaultOffset(SW * 0.715, valueUpgradeInfo.y + valueUpgradeInfo.h,
                                      "Cost: " + to_string(1) + " Perk", 16, 3,
                                      LUColor,
                                      painter.darkBrown, painter.black);
    valueUpgradeBtn.handleUpgradeClick(gameData.boxLimitUpgrade, gameData.perk, 1);
}

void Game::draw_setting_tab()
{
    settingTabMenu.drawDefaultOffset(SW * (0.7 + 0.3 * 2 / 3) + 15,
                                     SH * 0.88, "", 0, 3, painter.darkBrown, painter.black,
                                     painter.white, false, setting_icon, 0.7);
    graphics.drawCenterOfText("Settings", 25, painter.white, SW * 0.85,
                              SH * 0.05);
    graphics.drawRect(SW * 0.73, SH * 0.08, SW * 0.24, SH * 0.005, 0,
                      painter.white, painter.darkBrown, "line");
    string playTimeStr = "Play Time: " + to_string(static_cast<int>(gameData.playTime)) + "s";
    graphics.drawText(playTimeStr.c_str(), 12, painter.white, SW * 0.7 + 10,
                      SH * 0.83);

    /** Music **/
    if (musicPlayed && !musicPaused)
    {
        musicBtn.drawDefaultOffset(SW * 0.715, SH * 0.1, "Music: On", 16, 3,
                                   painter.lightGrey, painter.darkBrown, painter.black);
    }
    else
    {
        musicBtn.drawDefaultOffset(SW * 0.715, SH * 0.1, "Music: Off", 16, 3,
                                   painter.grey, painter.darkBrown, painter.black);
    }
    musicBtn.handleMusicClick(gameData, musicPaused);

    // graphics.playMusic()
}

void Game::draw_stats()
{
    perkStat.draw(SW * 0.61, SH * 0.05, "Perk: " + to_string(gameData.perk), 12,
                  5, painter.grey, painter.cyan, painter.white, false);
    scoreStat.draw(SW * 0.61 - SW * 0.17, SH * 0.05,
                   "Score: " + to_string(gameData.score), 12, 5, painter.grey, painter.green, painter.white, false);
    /** Limit **/
    string limit_str = "Box: " + to_string(gameData.availableBoxes) + '/' + to_string(
        gameData.boxLimitUpgrade[0]);
    graphics.drawText(limit_str.c_str(), 13, painter.white, SW * 0.5, SH * 0.97);
    /***** XP BAR *****/
    int xpNeeded = gameData.xpToNextLevel();
    graphics.drawRect(SW * 0.025, SH * 0.019, SW * 0.3, SH * 0.065, 0, painter.lightGrey, painter.white, "XP Bar");
    double xp_progess = static_cast<double>(gameData.xp) / xpNeeded;
    double xpBarWidth = SW * 0.29 * xp_progess;
    graphics.drawRect(SW * 0.03, SH * 0.026, xpBarWidth, SH * 0.055, 0, painter.blue);
    string xp_str = "XP: " + to_string(gameData.xp) + "/" + to_string(xpNeeded);
    graphics.drawCenterOfText(xp_str.c_str(), 16, painter.white, SW * 0.15, SH * 0.05);
    /***** Tier Box *****/
    graphics.drawRect(SW * 0.01, SH * 0.15, SW * 0.115, SH * 0.21, 2, painter.lightGrey, painter.white, "Tier Box");
}

void Game::music_init()
{
    if (gameData.musicPlaying && !musicPlayed && !musicPaused)
    {
        graphics.playMusic(musicx, true);
        Mix_Volume(-1, gameData.musicVolume);
        musicPlayed = true;
        SDL_Log("Music Started...");
    }
}

void Game::timer()
{
    currTime = SDL_GetTicks();
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
//     graphics.drawRect(SW * 0.7, SH * 0.05, SW * 0.3, SH * 0.02, 0,
//                       painter.lightGrey, painter.white, "XP Bar");
//     int xpBarWidth = SW * 0.3 * (gameData.xp - gameData.xpToLevelUp[gameData.level - 1])
//         / (gameData.xpToLevelUp[gameData.level] - gameData.xpToLevelUp[gameData.level - 1]);
//     graphics.drawRect(SW * 0.7, SH * 0.05, xpBarWidth, SH * 0.02, 0, painter.green,
//                       painter.white);
//     graphics.drawText(to_string(gameData.xp).c_str(), 12, painter.white, SW * 0.7 + 10,
//                       SH * 0.05 + 5);
//     graphics.drawText(to_string(gameData.xpToLevelUp[gameData.level]).c_str(), 12, painter.white,
//                       SW * 0.7 + SW * 0.3 - 30, SH * 0.05 + 5);
// }
