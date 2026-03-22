#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool decodage_ligne(istringstream& line, vector <double>& tabValeurs);
vector<double> lectureLigne(istringstream& data, vector <double>& tabValeurs);