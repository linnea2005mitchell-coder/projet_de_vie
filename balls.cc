#include <iostream> 
#include <cmath>
#include <vector>
using namespace std;

#include "balls.h"

vector<Ball> stock; 

// faire le check sur nb_ball dans l'interception
// update les dependances dans le make files pr utiliser message & arenasize
bool verif_balls(double& x, double& y, double& r, double& dx, double& dy){
    
    verif_delta(dx,dy);

    if (verif_outside(x,y,r)) { // zone
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