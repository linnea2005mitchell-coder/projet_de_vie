# projet_de_vie
le fun

checker les conventions : 
- methodes dans .cc

Définitions: mettre tous les include iostream et compagnie dans les fichiers.cc,
    dans les fichiers.h ne mettre que ce qui est nécessaire dans ce .h (ex: include string ou vector) 
    (ne pas mettre iostream car très lourd) ==>on ne peut pas utiliser cout dans un fichier.h
    ==>remplacer string, vector, ifstream, etc. par std::string, std::vector, std::ifstream, etc dans les .h

Syntaxe de lancement: dans terminal: ./project t01.txt
    si affiche No such file or directory s'assurer que make a bien été fait (doit afficher: Nothing to be done for 'all'.)

Faire:  corriger lecture paddle
        fonctions vérif score et lives


backup project parce que je dois le supp parce qu'il y en a 2 idk why: 
#include <iostream>
#include <string>
#include <gtkmm/application.h>
#include "game.h"
#include "gui.h"
using namespace std;


int main(int argc, char* argv[]){
    Game game( 0, 0, {}, {}, {});
    string file_name("");

    if(argc>1){
        file_name = argv[1];
        lecture_fichier(argv[1], game);
    }

    auto app = Gtk::Application::create();
    return app->make_window_and_run<My_window>(1, argv, file_name, std::move(game));

    return 0;
}
