#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "game.h"
#include "message.h"
using namespace std;
 
enum EtatLecture {SCORE, LIVES, PADDLE, NB_BRICKS, BRICKS, NB_BALLS, BALLS};
constexpr size_t NB_VAL_PAD(3); 
constexpr size_t NB_VAL_BRICK(4);
constexpr size_t NB_VAL_BALL(5);
static unsigned etat(0);

void lecture_fichier(const string& nomFichier, Game& game){ 
    ifstream fichier("tests/" + nomFichier);      //changer "tests/"" avec nom dossier
    if(fichier.fail()){
        cout << "Impossible d'accéder au fichier." << endl;
        exit(EXIT_FAILURE);
    }

    int compteur(0);
    string line;
    vector<double> tabVal;

    while(getline(fichier >> ws, line)){
        if(line[0]=='#') continue; 
        istringstream data(line);
        if(lecture_ligne(data, tabVal, compteur, game)) exit(EXIT_FAILURE);
    }
    
    cout << message::success() << endl;
    fichier.close();
    exit(EXIT_SUCCESS);
}

bool lecture_ligne(istringstream& data, vector<double>& tabVal, int& compteur, Game& game){
    double valeur(0);
    while(data>>valeur){ 
        switch(etat){
            case SCORE:
            case LIVES: if(verif_ligne(valeur, tabVal, game)) return true; 
                break; 
            case PADDLE: 
                if(tabVal.size() != NB_VAL_PAD) tabVal.push_back(valeur);
                if(tabVal.size() == NB_VAL_PAD){
                    if(verif_ligne(valeur, tabVal, game)) return true; 
                }
                break;
            case NB_BRICKS:
            case NB_BALLS: compteur = valeur; 
                etat++; break;
            case BRICKS:
                if (lecture_brick(valeur, compteur, tabVal, game)) return true; 
                break;
            case BALLS: 
                if(compteur>0){
                    if(tabVal.size() < NB_VAL_BALL) tabVal.push_back(valeur);
                    if(tabVal.size()==NB_VAL_BALL){
                        compteur--;
                        if(verif_ligne(valeur, tabVal, game)) return true;
                    }
                }
                break;
            default: break;
        }
    }
    return false;
}

bool verif_ligne(int valeur, vector <double>& tabVal, Game& game){ 
    switch(etat){
        case SCORE: 
            etat++;
            if(verif_score(valeur, game.score())) return true;
            break;
	    case LIVES:
            etat++;
            if(verif_lives(valeur, game.lives())) return true;
            break;
        case PADDLE:
            etat++;
            if(verif_paddle(tabVal[0], tabVal[1], tabVal[2], game.pad())) return true;
            tabVal.clear();	break;
        case BRICKS:
            if(verif_brick(tabVal[0], tabVal[1], tabVal[2], tabVal[3], tabVal[4], 
               game.stockBrick()) or intersects_brick_paddle(game)) return true;   
            tabVal.clear();	break;
        case BALLS:
            if(verif_ball(tabVal[0], tabVal[1], tabVal[2], tabVal[3], tabVal[4], 
               game.stockBall()) or intersects_ball_brick(game) 
               or intersects_paddle_ball(game)) return true;
            tabVal.clear(); break;
	    default: 
            break;  
    }
    return false;
}

bool lecture_brick(double valeur, int& compteur, vector<double>& tabVal, Game& game){
    if(compteur>0){
        if(tabVal.size() < NB_VAL_BRICK) tabVal.push_back(valeur);
        else if(tabVal.size()==NB_VAL_BRICK && tabVal[0]==0){
            compteur--;
            tabVal.push_back(valeur);
            if(verif_ligne(valeur, tabVal, game)) return true; 
        }
        if(tabVal.size()==NB_VAL_BRICK && tabVal[0]!=0){
            compteur--;
            tabVal.push_back(-1);
            if(verif_ligne(valeur, tabVal, game)) return true; 
        }
    }
    if(compteur==0) etat++; 
    return false;
}

bool verif_score(int& score, int& scoreGame){ 
    if (score<0){
        cout << message::invalid_score(score)<< endl;
        return true;
    }
    scoreGame = score;
    return false;
}

bool verif_lives(int& live, int& liveGame){
    if (live<0){
        cout<< message::invalid_lives(live)<< endl;
        return true;
    }
    liveGame = live;
    return false;
}

bool intersects_brick_paddle(Game& game){ 
    Brick derniere = *game.stockBrick().back(); 
    if (game.pad().corps().intersects(derniere.corps())) {
        cout << message::collision_paddle_brick(game.stockBrick().size()-1) << endl;
        return true; 
    }
    return false;
}

bool intersects_ball_brick(Game& game){ 
    int k(0);
    Ball derniere = game.stockBall().back(); 
    for (const auto& brick : game.stockBrick()) {
        if (derniere.intersects((*brick).corps())) {  
            cout << message::collision_ball_brick(game.stockBall().size()-1, size_t(k)) << endl;
            return true; 
        }
        k++;
    }
    return false;
}

bool intersects_paddle_ball(Game& game){
    Ball derniere = game.stockBall().back();
        if (derniere.intersects(game.pad().corps())) {
         cout << message::collision_paddle_ball(game.stockBall().size()-1) << endl;
            return true; 
        }
        return false;
}

void ecriture_fichier(const string& file_name, const Game& game){
    ofstream file(file_name);


}