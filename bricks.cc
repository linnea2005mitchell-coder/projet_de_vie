#include <iostream> 
#include <cmath>
#include <vector>
#include "bricks.h"
using namespace std;

enum BrickType {RAINBOW, BALLBRICK, SPLIT};
enum HitPoints {ROUGE=1, ORANGE, JAUNE, VERT, CYAN, BLEU, VIOLET};
constexpr int NB_INVALID_HITPOINTS(6);

bool verif_bricks(const double& type, const double& x, const double& y, 
                  const double& c, const double& hitpoints, Game& game){ 
    double halfC = c / 2.0;
    if (verif_outside(x, y, halfC)) { 
        cout << message::brick_outside(x, y) << endl; 
        return false;
    };
    
    if (c < brick_size_min){
        cout << message::invalid_brick_size(c) << endl;
        return false;
    };

    if ((type != RAINBOW) && (type != BALLBRICK) && (type != SPLIT)){
        cout << message::invalid_brick_type(type) << endl; 
        return false;
    };

    if (type == RAINBOW){
        if(verif_hitpoints(hitpoints)){
            cout << message::invalid_hit_points(hitpoints) << endl; 
            return false;
        };
    };

    Brick nouvelle(type, x, y, c, hitpoints);
    
    int compteur(0);
    for (const auto& b : game.stockBrick) {
        if (nouvelle.intersects(b)) {  
            cout << message::collision_bricks(size_t(compteur), game.stockBrick.size()) << endl;  
            return false; 
        };
        compteur++;
    };
    game.stockBrick.push_back(nouvelle);
    return true;
};// ajouter intersect avec paddle

bool verif_hitpoints(const double& hitpoints){
    int compteur(0);
    for(int i(ROUGE); i<= VIOLET; i++){
        if (hitpoints != i)
            compteur++;
    };
    if(compteur != NB_INVALID_HITPOINTS)
        return true;
    return false;
};
