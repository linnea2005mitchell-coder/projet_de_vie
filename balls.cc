#include <iostream> 
#include <cmath>
#include <vector>
using namespace std;

#include "balls.h"

bool verif_balls(double& x, double& y, double& r, double& dx, double& dy, 
                 vector<Ball>& stockBall){
    
    if(verif_delta(dx,dy)) return false;

    if (verif_outside(x,y,r)) { // zone
        cout << message::ball_outside(x,y)<< endl;
        return false;
    };

    Ball nouvelle(x, y, r, dx, dy);
    
    int c(0);
    for (const auto& b : stockBall) {
        if (nouvelle.intersects(b)) {  //check intersection
            cout << message::collision_balls(size_t(c), stockBall.size()) << endl;
            return false; 
        };
        c++;
    };

    stockBall.push_back(nouvelle);
    return true;
};