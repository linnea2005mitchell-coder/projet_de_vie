#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "game.h"
#include "message.h"

using namespace std;
 
enum EtatLecture {IGNORE=1, SCORE, LIVES, PADDLE, BRICKS, BALLS};
constexpr int NB_VALEURS(5);
static unsigned etat(0); 

void lectureFichier(const string& nomFichier, Game& game){ 
    ifstream fichier("tests/" + nomFichier); 
    if(fichier.fail()){
        cout << "Impossible d'accéder au fichier." << endl;
        exit(EXIT_FAILURE);
    }

    unsigned compteur(0);
    unsigned compteurB(0);
    string line;

    while(getline(fichier >> ws, line)){
        if(line[0]=='#'){
            ++compteur;
            etat = compteur;
            continue;
        }  

        if((etat==BRICKS) and compteurB==0){
            ++compteurB;  
        }
        else if ((etat==BALLS) and compteurB==1){
            ++compteurB;  
        }
        else{
            istringstream data(line);
            if(verif_ligne(data, game)){ 
                exit(EXIT_FAILURE);
            } 
        }
    }
    cout << message::success() << endl;
    fichier.close();
    exit(EXIT_SUCCESS);
}

bool verif_ligne(istringstream& data, Game& game){ 
    int valeur(0);
    vector <double> tabValeurs (NB_VALEURS, 0);
    switch(etat){
        case IGNORE:             
            break;
        case SCORE: 
            data >> valeur;
            return(verif_score(valeur, game.score));
            break;

	    case LIVES:
            data >> valeur;
            return(verif_lives(valeur, game.lives));
		    break;
        
        case PADDLE:
            lectureLigne(data, tabValeurs);
            return(verif_paddle(tabValeurs[0], tabValeurs[1], tabValeurs[2], game.pad));	
		    break;
        
        case BRICKS:
            lectureLigne(data, tabValeurs);
            return(verif_bricks(tabValeurs[0], tabValeurs[1], tabValeurs[2], 
                                tabValeurs[3], tabValeurs[4], game.stockBrick) 
                                or intersects_brick_paddle(game));	
		    break;

        case BALLS:
            lectureLigne(data, tabValeurs);
            return (verif_balls(tabValeurs[0], tabValeurs[1], tabValeurs[2], 
                                tabValeurs[3], tabValeurs[4], game.stockBall) 
                                or intersects_ball_brick(game) or intersects_paddle_ball(game)); 
		    break;

	    default: 
            break;  
    }
    return false;
}

void lectureLigne(istringstream& data, vector <double>& tabValeurs){
    for(int i(0); i<NB_VALEURS; ++i){
        data >> tabValeurs[i]; 
    }
}

bool verif_score(int& score, int& scoreGame){ 
    if (score<0){
        cout << message::invalid_score(score)<< endl;
        return true;
    };
    scoreGame = score;
    return false;
}

bool verif_lives(int& live, int& liveGame){
    if (live<0){
        cout<< message::invalid_lives(live)<< endl;
        return true;
    };
    liveGame = live;
    return false;
}

bool intersects_brick_paddle(const Game& game){ //vérif dernière brick avec paddle. true=intersection, false=pas d'intersection
    int c(0);
    for (const auto& brick : game.stockBrick) {
        if (game.pad.intersects(brick)) {  //check intersection
            cout << message::collision_paddle_brick(size_t(c)) << endl;
            return true; 
        };
        c++;
    }
    return false;
}


bool intersects_ball_brick(const Game& game){ //vérif dernière balle avec stock de brique. true = intesection
    int k(0);
    Ball derniere = game.stockBall[game.stockBall.size()-1]; //un peu moche. autre façon de faire?
    for (const auto& brick : game.stockBrick) {
        if (derniere.intersects(brick)) {  
            cout << message::collision_ball_brick(game.stockBall.size()-1, size_t(k)) << endl;
            return true; 
        };
        k++;
    };
    return false;
}

bool intersects_paddle_ball(const Game& game){

    Ball derniere = game.stockBall[game.stockBall.size()-1];
        if (derniere.intersects(game.pad)) {
         cout << message::collision_paddle_ball(game.stockBall.size()-1) << endl;
            return true; 
        };
        return false;
}