#include <iostream>
#include <SDL_main.h>
#include "game.hpp"


using namespace std;

int main(int argc, char* argv[])
{
    srand(time(nullptr));
    Game game;
    game.run();
    return 0;
}
