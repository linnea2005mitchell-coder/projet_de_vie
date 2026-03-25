#include <iostream> 
#include <cmath>
#include <vector>
#include "constants.h"
#include "message.h"
#include "bricks.h"
using namespace std;

enum BrickType {RAINBOW, BALLBRICK, SPLIT};
enum HitPoints {ROUGE=1, ORANGE, JAUNE, VERT, CYAN, BLEU, VIOLET};
constexpr int NB_INVALID_HITPOINTS(6);

vector<Brick> stockBrick; //mettre dans game? En tout cas pas le droit aux variables globales

bool verif_bricks(const double& type, const double& x, const double& y, 
                           const double& c, const double& hitpoints){ 
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
        if(verif_hitpoints(hitpoints)){
            cout << "message: invalid_hit_points" << endl; //message::invalid_hit_points(hitpoints);
            return false;
        };
    };

    Brick nouvelle(type, x, y, c, hitpoints);
    
    int compteur(0);
    for (const auto& b : stockBrick) {
        if (nouvelle.intersects(b)) {  
            cout << "message: collision_bricks" << endl; //message::collision_bricks(size_t(compteur), stock.size()); 
            return false; 
        };
        compteur++;
    };
    stockBrick.push_back(nouvelle);
    return true;
};

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
