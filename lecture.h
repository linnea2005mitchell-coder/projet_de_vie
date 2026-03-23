#ifndef LECTURE_H
#define LECTURE_H
#include <sstream>
#include <string>
#include <vector>

bool decodage_ligne(std::istringstream& data, std::vector<double>& tabValeurs);
void lectureLigne(std::istringstream& data, std::vector<double>& tabValeurs);
void lectureFichier();

#endif
