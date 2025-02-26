/*
* Author: Hannah Ross, Lily Norton, Galya Ramos
* Assignment Title: FINAL PROJECT
* Assignment Description: Falling Balls
* Due Date: 12/08/2024
* Date Created: 11/15/2024
* Date Last Modified: 12/08/2024
*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include "SDL_Plotter.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "games.hpp"

using namespace std;

int main() {
    SDL_Plotter p(800, 600);
    Game game(p);
    game.run();
    
    SDL_Quit();
    return 0;
    
}
