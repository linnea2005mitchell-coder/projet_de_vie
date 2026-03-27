#include <iostream> 
#include <cmath>
#include <vector>
using namespace std;

#include "balls.h"

bool verif_balls(double& x, double& y, double& r, double& dx, double& dy, 
                 vector<Ball>& stockBall){
    
    if(verif_delta(dx,dy)) return true;

    if (verif_outside(x,y,r)) { 
        cout << message::ball_outside(x,y)<< endl;
        return true;
    };

    Ball nouvelle(x, y, r, dx, dy);
    
    int c(0);
    for (const auto& ball : stockBall) {
        if (nouvelle.intersects(ball)) {  
            cout << message::collision_balls(size_t(c), stockBall.size()) << endl;
            return true; 
        };
        c++;
    };

    stockBall.push_back(nouvelle);
    return false;
};