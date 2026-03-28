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
    Paddle pad;
    std::vector<Brick> stockBrick;
    std::vector<Ball> stockBall;
};

void lecture_fichier(const std::string& nomFichier, Game& game);
bool lecture_ligne(std::istringstream& data, std::vector<double>& tabVal, 
                   int& compteur, Game& game);
bool verif_ligne(int valeur, std::vector <double>& tabVal, Game& game);
bool lecture_brick(double valeur, int& compteur, std::vector<double>& tabVal, 
                    Game& game);
bool verif_score(int score, int& scoreGame);
bool verif_lives(int live, int& liveGame);
bool intersects_brick_paddle(const Game& game);
bool intersects_ball_brick(const Game& game);
bool intersects_paddle_ball(const Game& game);

#endif 
