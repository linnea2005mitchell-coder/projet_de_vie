#ifndef GAME_H
#define GAME_H
#include <sstream>
#include <string>
#include <vector>
#include "balls.h"
#include "bricks.h"
#include "paddle.h"

class Game {
public : 
   Game(int s, int l, double x, double y ,double r) 
   : score_(s), lives_(l), pad_(x,y,r) {}
   int score() const {return score_ ;}
   int lives() const {return lives_ ;}
   Paddle pad() const {return pad_;}
   vector<Brick> stockBrick() const {return stockBricks;}
   vector<Ball> stockBall() const {return stockBalls;}
   

private: 
    int score_;
    int lives_;
    Paddle pad_;
    std::vector<Brick> stockBricks;
    std::vector<Ball> stockBalls;
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
