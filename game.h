#ifndef GAME_H
#define GAME_H
#include <sstream>
#include <string>
#include <vector>

bool decodage_ligne(std::istringstream& data, std::vector<double>& tabValeurs);
void lectureLigne(std::istringstream& data, std::vector<double>& tabValeurs);
void lectureFichier(const std::string& nomFichier);
bool verif_score(int& score);
bool verif_lives(int& live);

#endif
