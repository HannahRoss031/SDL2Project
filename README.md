# Falling Balls Project (SDL2)

## Authors:  
**Hannah Ross, Lily Norton, and Galya Ramos**  

The assignment was to create and code a game similar to the global falling balls game, a simple game including dropping balls from various heights and attempting to collide with colorful balls at the bottom for points.

## Game Objective: 
- Control the player ball and drop it strategically.
- Hit stationary balls at the bottom to earn points.
- If the ball touches the floor without hitting any target, the game ends.
- The game allows multiple attempts, resetting the ball if the player scores at least one point.

## Gameplay & Controls
- Movement: A (Left), D (Right)
- Drop Ball: F (Releases the player ball)
- Collisions:
  - If the player ball hits a stationary ball, it bounces and can hit more balls.
  - Each hit increases the score, with small circles (1 point) and big circles (5 points) displayed in the top-left corner.
- Game Over: If the player's ball hits the floor without scoring, the game ends.


## Features: 
- Randomized stationary balls at the bottom for replayability
- Realistic physics-based bouncing on collision
- Score tracking with visual indicators
- Smooth keyboard controls

### Code Language: C++
### Libraries/Tools: SDL2, MingW
### Compiler: g++ main.cpp -o program.exe

## How to Play: 
1. Run the game by executing the compiled program.
2. Move the player ball left (A) or right (D).
3. Drop the ball (F) and aim for stationary balls!
4. Score as many points as possible before losing!

