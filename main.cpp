#include <iostream>
#include <SDL_main.h>
#include "game.h"
#include "components/button.h"


using namespace std;

int main(int argc, char *argv[]) {
    Game game;
    game.run();
    return 0;
}
