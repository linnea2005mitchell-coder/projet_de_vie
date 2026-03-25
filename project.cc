#include <iostream>
#include <string>
#include "game.h"
using namespace std;


int main(int argc, char* argv[]){

    Game game{0, 0, {}, {}, Paddle{}};
    if(argc>1)
        lectureFichier(argv[1], game);
    cout << "Etat du jeu:" << game.score << game.lives;

    return 0;
}

