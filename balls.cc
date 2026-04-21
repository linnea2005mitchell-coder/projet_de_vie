#include <iostream> 
#include <cmath>
#include <vector>
using namespace std;

#include "balls.h"

bool verif_ball(double x, double y, double r, double dx, double dy, 
                vector<Ball>& stockBall){

    if ((x-r) < 0 || y < 0 || (x+r) > arena_size || (y+r) > arena_size) { 
        cout << message::ball_outside(x, y) << endl; 
        return true;
    }

    Ball nouvelle(x, y, r, dx, dy);
    
    int c(0);
    for (const auto& ball : stockBall) {
        if (nouvelle.intersects(ball.corps())) {  
            cout << message::collision_balls(size_t(c), stockBall.size()) << endl;
            return true; 
        }
        c++;
    }

    if(verif_delta(dx,dy)) return true;

    stockBall.push_back(nouvelle);
    return false;
};

bool verif_delta(double dx, double dy){
    if (sqrt(dx*dx + dy*dy) > delta_norm_max) {
        cout << message::invalid_delta(dx,dy) << endl;
        return true; 
    }
    return false; 
}

void Ball::drawBall() const{
    corps_.drawFull();
}