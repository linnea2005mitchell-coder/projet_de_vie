#include <iostream> 
#include <cmath>
#include "constants.h"
#include "message.cc"
using namespace std;

#include "balls.h"

// faire le check sur nb_ball dans l'interception
// update les dependances dans le make files pr utiliser message & arenasize
bool verif_balls(double& x, double& y, double& r, double& dx, double& dy){
    
    verif_delta(dx,dy);

    if (((x-r) < 0) || ((y-r) < 0) || ((x+r) > arena_size) || ((y+r) > arena_size)) { // zone
        message::ball_outside(x,y);
        return false;
    };

    Ball nouvelle(x, y, r, dx, dy);
    
    int c(0);
    for (const auto& b : stock) {
        if (nouvelle.intersects(b)) {  //check intersection
            message::collision_balls(size_t(c), stock.size()); 
            return false; 
        };
        c++;
    };

    stock.push_back(nouvelle);
    return true;
};