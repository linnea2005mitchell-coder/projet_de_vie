#include <iostream> 
#include <cmath>
#include <vector>
using namespace std;

#include "balls.h"

bool verif_balls(double& x, double& y, double& r, double& dx, double& dy, 
                 vector<Ball>& stockBall){
    
    if(verif_delta(dx,dy)) return false;

    if (verif_outside(x,y,r)) { 
        cout << message::ball_outside(x,y)<< endl;
        return false;
    };

    Ball nouvelle(x, y, r, dx, dy);
    
    int c(0);
    for (const auto& ball : stockBall) {
        if (nouvelle.intersects(ball)) {  //check intersection
            cout << message::collision_balls(size_t(c), stockBall.size()) << endl;
            return false; 
        };
        c++;
    };

    int k(0);
    for (const auto& brick : stockBricks) {
        if (nouvelle.intersects(brick)) {  //check intersection
            cout << message::collision_ball_brick(size_t(k), stockBall.size()) << endl;
            return false; 
        };
        k++;
    };

    if (nouvelle.intersects(pad)) {
         cout << message::collision_paddle_ball(stockBall.size()) << endl;
         return false; 
    }

    stockBall.push_back(nouvelle);
    return true;
};