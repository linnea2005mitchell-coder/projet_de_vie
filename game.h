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
   Game(int s, int l, Paddle p, std::vector<Brick> sbrick, std::vector<Ball> sball) 
   : score_(s), lives_(l), pad_(p), stockBricks(sbrick), stockBalls(sball) {}
   int& score() {return score_ ;}
   int& lives() {return lives_ ;}
   Paddle& pad() {return pad_;}
   std::vector<Brick>& stockBrick() {return stockBricks;} //faire collection hétérogène?
   std::vector<Ball>& stockBall() {return stockBalls;}
   

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
bool verif_score(int& score, int& scoreGame);
bool verif_lives(int& live, int& liveGame);
bool intersects_brick_paddle(Game& game);
bool intersects_ball_brick(Game& game);
bool intersects_paddle_ball(Game& game);

#endif 
