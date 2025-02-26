/*
* Author: Hannah Ross, Lily Norton, Galya Ramos 
* Assignment Title: FINAL PROJECT
* Assignment Description: Falling Balls
* Due Date: 12/08/2024
* Date Created: 11/15/2024
* Date Last Modified: 12/08/2024
*/

#ifndef games_hpp
#define games_hpp
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "SDL_Plotter.h"

using namespace std;
const double PI = 3.14159265359;
const int raidus = 10; 
struct Ball {
    double x, y;
    double radius;
    double velocity, velocityX, velocityY;
    bool isFalling;
    //Ball();
    Ball(double xPos, double yPos, double ballRadius, double ballSpeed, bool falling);
    void applyGravity(Ball &ball);
};
class Game {
private:
    SDL_Plotter &plotter;
    Ball playerBall;
    Ball targetBall;
    bool gameOver, ballSpawned;
    vector<Ball> ball;
    vector<Ball> stationary_balls;
    int score;
    int scoreAtBallDrop;
    bool dragging;  // Tracks if the mouse is being dragged
    int mouseX, mouseY;
    int passesAtBottom; 
public:
    //design?
    SDL_Renderer* renderer;  
    SDL_Window* window;
    void drawBoxOnBottomHalf(SDL_Plotter& plotter);
    void drawSkull(SDL_Plotter& plotter, int x, int y);
    //code
    Game(SDL_Plotter &p);
    void run();
    deque<int> lastYValues;
    deque<int> clearScreen;
    void nothing(); 
    void drawScore();
    void drawGradientBackground();
    void drawTopBox(); 
    void drawBottomBox(); 
    bool isBallAtBottom(); 
    void updateBalls();
    void initStaionaryBalls(int); 
    void updatePlayerBall();
    void handleInput();
    void handleWalls();
    bool checkBallCollision(Ball &ball1, Ball &ball2);
    bool checkCollision();
    void handleCollision();
    void processCollision(Ball &playerBall, Ball &targetBall);
    void drawPlayerBalls();
    void drawStationaryBalls();
    void drawBall(Ball &ball);
    void reset();
};
#endif /* games_hpp */
