#include <iostream> 
#include <cmath>
#include <vector>
#include "bricks.h"
using namespace std;

enum BrickType {RAINBOW, BALLBRICK, SPLIT};
enum HitPoints {ROUGE=1, ORANGE, JAUNE, VERT, CYAN, BLEU, VIOLET};
constexpr int NB_INVALID_HITPOINTS(6);

bool verif_brick(double type, double x, double y, double c, double hitpoints, 
                 std::vector<Brick>& stockBrick){      
    if ((type != RAINBOW) && (type != BALLBRICK) && (type != SPLIT)){
        cout << message::invalid_brick_type(type) << endl; 
        return true;
    }              

    double halfC = c / 2.0;
    if ((x-halfC) < 0 || (y-halfC) < 0 || (x+halfC) > arena_size 
        || (y+halfC) > arena_size) { 
        cout << message::brick_outside(x, y) << endl; 
        return true;
    }

    if (c < brick_size_min){
        cout << message::invalid_brick_size(c) << endl;
        return true;
    }

    if (type == RAINBOW){
        if(verif_hitpoints(hitpoints)){
            cout << message::invalid_hit_points(hitpoints) << endl; 
            return true;
        }
    }

    Brick nouvelle(type, x, y, c, hitpoints);
    int compteur(0);
    for (const auto& b : stockBrick) {
        if (nouvelle.intersects(b)) {  
            cout << message::collision_bricks(size_t(compteur), stockBrick.size()) 
            << endl;  
            return true; 
        }
        compteur++;
    }
    stockBrick.push_back(nouvelle);
    return false;
} 

bool verif_hitpoints(double hitpoints){
    int compteur(0);
    for(int i(ROUGE); i<= VIOLET; i++){
        if (hitpoints != i)
            compteur++;
    }
    if(compteur != NB_INVALID_HITPOINTS) return true;
    return false;
}
