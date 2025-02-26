/*
* Author: Hannah Ross, Lily Norton, Galya Ramos
* Assignment Title: FINAL PROJECT
* Assignment Description: Falling Balls
* Due Date: 12/08/2024
* Date Created: 11/15/2024
* Date Last Modified: 12/08/2024
*/

#include <stdio.h>
#include "games.hpp"
#include "SDL_Plotter.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

const int RADIUS_C = 20;
 
Ball::Ball(double xPos, double yPos, double ballRadius, double ballSpeed, bool Falling): x(xPos), y(yPos), radius(ballRadius), isFalling(Falling){}
Game::Game(SDL_Plotter &p):
plotter(p),
playerBall(300, 100, RADIUS_C, 0.5, false),
targetBall(300, 600, RADIUS_C, 0, false),
gameOver(false),
dragging(false),
mouseX(0), mouseY(0),
score(0),
ballSpawned(false) {
    initStaionaryBalls(50);
    
}
Uint32 backgroundColor = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), 255, 182, 193);  // Pink background
void Game::run(){
    while(!plotter.getQuit()){
        plotter.clear();
        plotter.setBackgroundColor(backgroundColor);
        drawTopBox();
        drawBoxOnBottomHalf(plotter);
        handleInput();
        handleCollision();
        drawScore();
        handleWalls();
        updateBalls();
        drawStationaryBalls();
        drawPlayerBalls();
        plotter.update();
        updatePlayerBall();
        if(isBallAtBottom()){
            reset();
        }
        if(gameOver){
            plotter.clear();
            score = 0;
            Uint32 backgroundColor2 = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), 0, 0, 0);
            plotter.setBackgroundColor(backgroundColor2);
            drawSkull(plotter, 300, 300);
            
            plotter.update();
        }
    
    }
}
void Game::drawSkull(SDL_Plotter& plotter, int x, int y) {
    
    int skullRadius = 60;
    int skullCenterX = x;
    int skullCenterY = y;
    for (int angle = 0; angle < 360; angle++) {
        int dx = skullRadius * cos(angle * M_PI / 180);
        int dy = skullRadius * sin(angle * M_PI / 180);
        plotter.plotPixel(skullCenterX + dx, skullCenterY + dy, 255, 255, 255); // white color
    }
    int eyeRadius = 10;
    int eyeOffsetX = 20;
    int eyeOffsetY = 15;
    for (int angle = 0; angle < 360; angle++) {
        int dx = eyeRadius * cos(angle * M_PI / 180);
        int dy = eyeRadius * sin(angle * M_PI / 180);
        plotter.plotPixel(skullCenterX - eyeOffsetX + dx, skullCenterY - eyeOffsetY + dy, 0, 0, 0); // black color
    }
    for (int angle = 0; angle < 360; angle++) {
        int dx = eyeRadius * cos(angle * M_PI / 180);
        int dy = eyeRadius * sin(angle * M_PI / 180);
        plotter.plotPixel(skullCenterX + eyeOffsetX + dx, skullCenterY - eyeOffsetY + dy, 0, 0, 0); // black color
    }
    plotter.plotPixel(skullCenterX, skullCenterY, 0, 0, 0);
    plotter.plotPixel(skullCenterX - 5, skullCenterY + 5, 0, 0, 0);
    plotter.plotPixel(skullCenterX + 5, skullCenterY + 5, 0, 0, 0);
    for (int i = -20; i <= 20; i++) {
        plotter.plotPixel(skullCenterX + i, skullCenterY + 25, 0, 0, 0);
    }
    plotter.plotPixel(skullCenterX - 10, skullCenterY - 15, 0, 0, 0);
    plotter.plotPixel(skullCenterX + 10, skullCenterY - 15, 0, 0, 0);
    
}
void Game::drawBoxOnBottomHalf(SDL_Plotter& plotter) {
    int screenWidth = 800;
    int screenHeight = 600;
    
    int boxX = 0;
    int boxY = screenHeight / 0.995;
    int boxWidth = screenWidth;
    int boxHeight = screenHeight / 2;
    int r = 173, g = 216, b = 230;
    
    for (int y = boxY; y < boxY + boxHeight; ++y) {
        for (int x = boxX; x < boxX + boxWidth; ++x) {
            plotter.plotPixel(x, y, r, g, b);
        }
    }
}
void Game::drawTopBox() {
    int boxWidth = 800;
    int boxHeight = 50;
    int boxX = 0;
    int boxY = 0;
    int r = 255, g = 182, b = 193;
    int stripeHeight = 5;
    for (int y = boxY; y < boxY + boxHeight; ++y) {
        if ((y / stripeHeight) % 2 == 0) {
            for (int x = boxX; x < boxX + boxWidth; ++x) {
                plotter.plotPixel(x, y, r, g, b);
            }
        }
        else {
            int r2 = 173, g2 = 216, b2 = 230;
            for (int x = boxX; x < boxX + boxWidth; ++x) {
                plotter.plotPixel(x, y, r2, g2, b2);
            }
        }
    }
}
bool Game::isBallAtBottom(){
    
    return playerBall.y + RADIUS_C >= 600;
    
   /* bool isBallAtBottom = playerBall.y + 30 >= 600;
        
    if(isBallAtBottom){
        passesAtBottom++;
        }
    else{
        passesAtBottom = 0;
    }
    
    return passesAtBottom > 850;*/
}
void Ball::applyGravity(Ball &ball){
    if(ball.isFalling){
        ball.velocityY += 0.003;
        ball.y += ball.velocityY;
        ball.x += ball.velocityX;
        
        if (ball.y >= 600 - ball.radius) {
            ball.y = 600 - ball.radius;
            ball.velocityY -= ball.velocityY * 0.002;
        }
    }
}
void Game::updatePlayerBall(){
    playerBall.applyGravity(playerBall);
}
void Game::reset(){
    playerBall.x = 300;
    playerBall.y = 100;
    
    playerBall.velocityX = 0;
    playerBall.velocityY = 0;
    
    playerBall.isFalling = false;
    
    ballSpawned = false;
    
    int noActionCount = 0;
    
        if (score == scoreAtBallDrop) {
            noActionCount++;
        } else {
            noActionCount = 0;
        }
        
        if (noActionCount >= 1) {
            gameOver = true;
        }
        
        scoreAtBallDrop = score;
        
}
void Game::updateBalls() {
    if(playerBall.y >= 600 - playerBall.radius && !ballSpawned){
        if (rand() % 50 == 0) {
                double xPos = rand() % 550;
                double yPos = rand() % 200 + 300;
             
                targetBall.x = xPos;
                targetBall.y = yPos;
            
                ballSpawned = true;
            }
    }
}
void Game::initStaionaryBalls(int num){
    for(int i = 0; i < num; ++i){
        
        double xPos = rand() % 750;
        double yPos = rand() % 200 + 400;
        double radius = rand() % 20 + 2;
        
        stationary_balls.push_back(Ball(xPos, yPos, radius, 0, false));
        
    }
}
void Game::handleInput(){
    if (plotter.kbhit()) {
           char key = plotter.getKey();
           if (key == 'a' || key == 'A') {
               if (playerBall.x > 0) playerBall.x -= 10; // Move left
           } else if (key == 'd' || key == 'D') {
               if (playerBall.x < 800 - playerBall.radius * 2) playerBall.x += 10; // Move right
           } else if (key == 'f' || key == 'F') {
               playerBall.isFalling = true;  
               ballSpawned = false;
           }
           else if(key == 'r' || key == ' '){
               gameOver = false;
               stationary_balls.clear();
               initStaionaryBalls(50);
           }
       }
}
void Game::drawPlayerBalls(){
    for(int i = -playerBall.radius; i <= playerBall.radius; i++){
        for(int j = -playerBall.radius; j <= playerBall.radius; j++){
            if(i * i + j * j <= playerBall.radius * playerBall.radius){
                
                int xPos = playerBall.x + i;
                int yPos = playerBall.y + j;
                
                if(xPos >= 0 && xPos < 800 && yPos >= 0 && yPos < 900){
                    plotter.plotPixel(xPos, yPos, 245, 245, 245);
                }
            }
        }
    }
}
void Game::drawScore(){
    if(score == 0){
        return;
    }
    int fivePoints = score / 5;
    int onePoint = score % 5;
    
    for(int i = 0; i < fivePoints; ++i){
        Ball tempBall = Ball((20 * i) + 20, 10, 10, 0, false);
        drawBall(tempBall);
    }
    for(int i = 0; i < onePoint; ++i){
        Ball tempBall = Ball((10 * i) + 20, 30, 5, 0, false);
        drawBall(tempBall);
    }
    
}
void Game::drawStationaryBalls(){
    for(int i = 0; i < stationary_balls.size(); ++i){
        drawBall(stationary_balls[i]);
    }
}
void Game::drawBall(Ball &ball){
    for (int i = -ball.radius; i <= ball.radius; i++) {
        for (int j = -ball.radius; j <= ball.radius; j++) {
            if (i * i + j * j <= ball.radius * ball.radius) {
                plotter.plotPixel(ball.x + i, ball.y + j, 255, 127, 80);  // Red target balls
            }
        }
    }
}
void Game::handleWalls(){
    if(playerBall.x - RADIUS_C < 0){
        playerBall.velocityX = -1 * playerBall.velocityX;
    }
    else if(playerBall.x + RADIUS_C > 600){
        playerBall.velocityX = -1 * playerBall.velocityX;
    }
}
bool Game::checkCollision(){
    // Calculate the distance between the centers of the two balls
    double dx = playerBall.x - targetBall.x;
    double dy = playerBall.y - targetBall.y;
    double distance = sqrt(dx * dx + dy * dy);  // Euclidean distance
    
    double radiiSum = playerBall.radius + targetBall.radius;
    
    return distance <= radiiSum;
}
bool Game::checkBallCollision(Ball &ball1, Ball &ball2){
    double dx = ball1.x - ball2.x;
    double dy = ball1.y - ball2.y;
    double distance = sqrt(dx * dx + dy * dy);
    
    double radiiSum = ball1.radius + ball2.radius;
    
    return distance <= radiiSum;
    
}
void Game::handleCollision(){
    vector<int> ballSlotsHit;
    for(int i = 0; i < stationary_balls.size(); ++i){
            if(checkBallCollision(playerBall, stationary_balls[i])){
                score++;
                processCollision(playerBall, stationary_balls[i]);
                ballSlotsHit.push_back(i);
                
            }
    }
    for(int i = (int)ballSlotsHit.size() - 1; i >= 0; --i){
        stationary_balls.erase(stationary_balls.begin() + ballSlotsHit[i]);
    }
    if(ballSlotsHit.size() > 0){
        initStaionaryBalls(1);
    }
    
}
void Game::nothing(){
    deque<int> clearScreen;
    
    for(int i = 0; i < stationary_balls.size(); ++i){
        if(gameOver){
            clearScreen.push_back(i);
        }
    }
    clearScreen.push_back(1);
    
    for(int i = (int)clearScreen.size() - 1; i >= 0; --i){
        stationary_balls.erase(stationary_balls.begin() + clearScreen[i]);
        //playerBall.erase();
    }
    
    
}
void Game::processCollision(Ball &playerBall, Ball &targetBall) {
    double dx = playerBall.x - targetBall.x;
    double dy = playerBall.y - targetBall.y;
    double distance = sqrt(dx * dx + dy * dy);
    double normalX = dx / distance;
    double normalY = dy / distance;
    double velocityX = playerBall.velocityX;
    double velocityY = playerBall.velocityY;
    double angleOfIncidence = atan2(velocityY, velocityX) - atan2(normalY, normalX);
    if (angleOfIncidence > M_PI) angleOfIncidence -= 2 * M_PI;
    if (angleOfIncidence < -M_PI) angleOfIncidence += 2 * M_PI;
    double dotProduct = velocityX * normalX + velocityY * normalY;
    playerBall.velocityX -= 2 * dotProduct * normalX;
    playerBall.velocityY -= 2 * dotProduct * normalY;
    
    playerBall.velocityX *= .8;  // lessen x velocity by 10%
    playerBall.velocityY *= .8;  // lessen y velocity by 10%
    
    double overlap = playerBall.radius + targetBall.radius - distance;
    playerBall.x += normalX * overlap;
    playerBall.y += normalY * overlap;
        
}
