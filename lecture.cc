#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "lecture.h"
#include "message.h"
//inclure les modules nécessaires
using namespace std;
 
enum etatLecture {IGNORE=1, SCORE, LIVES, PADDLE, BRICKS, BALLS};
constexpr int nbValeurs(5);
static unsigned etat(0); 

void lectureFichier(const string& nomFichier){ 
    ifstream fichier("tests/" + nomFichier); 
    if(fichier.fail()){
        cout << "Impossible d'accéder au fichier." << endl;
        exit(EXIT_FAILURE);
    }

    unsigned compteur(0);
    unsigned compteurB(0);
    string line;
    vector <double> tabValeurs (nbValeurs, 0);

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
            if(decodage_ligne(data, tabValeurs) == false){
                exit(EXIT_FAILURE);
            } 
        }
    }
    cout << message::success() << endl;
    fichier.close();
}

bool decodage_ligne(istringstream& data, vector <double>& tabValeurs){ //true=pas d'erreur, false=erreur
    double valeur(0);
    switch(etat)
        {
        case IGNORE:             
            break;
        case SCORE: 
            data >> valeur;
            return(true);	//changer true par nomfonction(valeur))
            break;

	    case LIVES:
            data >> valeur;
            return(true);	//changer true par nomfonction(valeur)
		    break;
        
        case PADDLE:
            data >> valeur;
            return(true);	//changer true par nomfonction(valeur)
		    break;
        
        case BRICKS:
            lectureLigne(data, tabValeurs);
            return(true);	//changer true par nomfonction(tabValeurs[0], tabValeurs[1], tabValeurs[2], tabValeurs[3], tabValeurs[4])
		    break;

        case BALLS:
            lectureLigne(data, tabValeurs);
            return (true);     //changer true par nomfonction(tabValeurs[0], tabValeurs[1], tabValeurs[2], tabValeurs[3], tabValeurs[4])
		    break;

	    default: 
            break;  
        }
    return true;
}

void lectureLigne(istringstream& data, vector <double>& tabValeurs){
    for(int i(0); i<nbValeurs; ++i){
        data >> tabValeurs[i]; 
    }
}
