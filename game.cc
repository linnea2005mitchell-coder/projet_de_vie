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
    vector <double> tabValeurs (NB_VALEURS, 0);

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
            if(decodage_ligne(data, tabValeurs, game) == false){
                exit(EXIT_FAILURE);
            } 
        }
    }
    cout << message::success() << endl;
    fichier.close();
    exit(EXIT_SUCCESS);
}

bool decodage_ligne(istringstream& data, vector <double>& tabValeurs, Game& game){ 
    int valeur(0);
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
                                tabValeurs[3], tabValeurs[4], game));	
		    break;

        case BALLS:
            lectureLigne(data, tabValeurs);
            return (verif_balls(tabValeurs[0], tabValeurs[1], tabValeurs[2], 
                                tabValeurs[3], tabValeurs[4], game)); 
		    break;

	    default: 
            break;  
    }
    return true;
}

void lectureLigne(istringstream& data, vector <double>& tabValeurs){
    for(int i(0); i<NB_VALEURS; ++i){
        data >> tabValeurs[i]; 
    }
}

bool verif_score(int& score, int& scoreGame){ 
    if (score<0){
        cout << message::invalid_score(score)<< endl;
        return false;
    };
    scoreGame = score;
    return true;
}

bool verif_lives(int& live, int& liveGame){
    if (live<0){
        cout<< message::invalid_lives(live)<< endl;
        return false;
    };
    liveGame = live;
    return true;
}