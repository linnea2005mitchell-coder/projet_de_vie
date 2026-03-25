#ifndef GAME_H
#define GAME_H
#include <sstream>
#include <string>
#include <vector>
#include "balls.h"
#include "bricks.h"
#include "paddle.h"

bool decodage_ligne(std::istringstream& data, std::vector<double>& tabValeurs);
void lectureLigne(std::istringstream& data, std::vector<double>& tabValeurs);
void lectureFichier(const std::string& nomFichier);
bool verif_score(int& score);
bool verif_lives(int& live);

#endif
