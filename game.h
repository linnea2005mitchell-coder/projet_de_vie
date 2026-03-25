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
};

void lectureFichier(const std::string& nomFichier, Game& game);
bool decodage_ligne(std::istringstream& data, std::vector<double>& tabValeurs, 
                    Game& game);
void lectureLigne(std::istringstream& data, std::vector<double>& tabValeurs);
bool verif_score(int& score, int& scoreGame);
bool verif_lives(int& live, int& liveGame);

#endif 
