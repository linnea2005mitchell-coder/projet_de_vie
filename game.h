#ifndef GAME_H
#define GAME_H
#include <sstream>
#include <string>
#include <vector>
#include "balls.h"
#include "bricks.h"
#include "paddle.h"

struct Game {
    int score;
    int lives;
    std::vector<Brick> stockBrick;
    std::vector<Ball> stockBall;
    Paddle pad;
};

void lectureFichier(const std::string& nomFichier, Game& game);
bool verif_ligne(std::istringstream& data, Game& game);
void lectureLigne(std::istringstream& data, std::vector<double>& tabValeurs);
bool verif_score(int& score, int& scoreGame);
bool verif_lives(int& live, int& liveGame);
bool intersects_brick_paddle(const Game& game);
bool intersects_ball_brick(const Game& game);
bool intersects_paddle_ball(const Game& game);

#endif 
