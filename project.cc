#include <iostream>
#include <string>
#include "game.h"
using namespace std;


int main(int argc, char* argv[]){

    infos donnees();

    if(argc>1)
        lectureFichier(argv[1], donnees);
    
    return 0;
}

