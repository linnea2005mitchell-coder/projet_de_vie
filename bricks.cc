#include <iostream> 
#include <cmath>
//#include "constants.h"
//#include "message.h"
#include "bricks.h"
using namespace std;

enum BrickType {RAINBOW, BALLBRICK, SPLIT};
enum HitPoints {ROUGE=1, ORANGE, JAUNE, VERT, CYAN, BLEU, VIOLET};
constexpr int NB_INVALID_HITPOINTS(6);

//À SUPPRIMER UNE FOIS QUE CONSTANTS.H EST INCLU
constexpr double arena_size = 100.0;
constexpr double brick_size_min = 3.;
//FIN SUPPRESSION

bool Brick :: verif_bricks(const double& type, const double& x, const double& y, const double& c, const double& hitpoints){ //attention dépasse 87
    cout << "liloulol" << endl; //supprimer
    double halfC = c / 2.0;
    if (((x-halfC) <= 0) || ((y-halfC) <= 0) || ((x+halfC) >= arena_size) || ((y+halfC) >= arena_size)) { 
        cout << "message: brick_outside" << endl; //message::brick_outside(x, y);
        return false;
    };
    
    if (c < brick_size_min){
        cout << "message: invalid_brick_size" << endl; //message::invalid_brick_size(c);
        return false;
    };

    if ((type != RAINBOW) && (type != BALLBRICK) && (type != SPLIT)){
        cout << "message: invalid_brick_type" << endl; //message::invalid_brick_type(type);
        return false;
    };

    if (type == RAINBOW){
        int compteur(0);
        for(int i(ROUGE); i<= VIOLET; i++){
            if (hitpoints != i)
                compteur++;
        };
        if(compteur != NB_INVALID_HITPOINTS) {
            cout << "message: invalid_hit_points" << endl; //message::invalid_hit_points(hitpoints);
            return false;
        };
    };

    //initialiser nouvelle brique (appeler fonction selon type de brique)
    return true;
}

int main(){  //à supprimer après
    Brick test(0, 3, 95, 4, 5);
    test.verif_bricks(test.getType(), test.x(), test.y(), test.cote(), test.getHitpoints());
    return 0;
}