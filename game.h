#ifndef GAME_H
#define GAME_H
#include <sstream>
#include <string>
#include <vector>
#include "balls.h"
#include "bricks.h"
#include "paddle.h"

struct infos{ 

vector<Ball> stockBall;
vector<Brick> stockBrick;
Paddle pad;

};

bool decodage_ligne(std::istringstream& data, std::vector<double>& tabValeurs);
void lectureLigne(std::istringstream& data, std::vector<double>& tabValeurs);
void lectureFichier(const std::string& nomFichier, infos& donnees);
bool verif_score(int& score);
bool verif_lives(int& live);

#endif
