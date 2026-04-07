#include <iostream>
#include <string>
#include "game.h"
using namespace std;


int main(int argc, char* argv[]){
    Game game( 0, 0, {}, {}, {});
    if(argc>1)
        lecture_fichier(argv[1], game);

    return 0;
}

