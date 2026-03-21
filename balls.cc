#include <iostream> 
#include <cmath>
#include "constants.h"
#include "message.cc"
using namespace std;

#include "balls.h"

// faire le check sur nb_ball dans l'interception
// update les dependances dans le make files pr utiliser message & arenasize
void verif_balls(double& x, double& y, double& r, double& dx, double& dy){
    
    double delta_norm(sqrt(dx*dx + dy*dy));
    if (delta_norm > delta_norm_max) {
        return message::invalid_delta(dx,dy);
    };
    if (((x-r) < 0) || ((y-r) < 0) || ((x+r) > arena_size) || ((y+r) > arena_size)) {
        return message::ball_outside(x,y);
    };
    //pushback la ball à stock 
}