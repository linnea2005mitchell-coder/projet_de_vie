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
        if (nouvelle.intersects(ball)) {  //check intersection
            cout << message::collision_balls(size_t(c), stockBall.size()) << endl;
            return true; 
        };
        c++;
    };

    //int k(0);
    //for (const auto& brick : stockBall) {
        //if (nouvelle.intersects(brick)) {  //check intersection
            //cout << message::collision_ball_brick(size_t(k), stockBall.size()) << endl;
            //return true; 
        //};
        //k++;
    //;

    //if (nouvelle.intersects(game.pad)) {
        // cout << message::collision_paddle_ball(game.stockBall.size()) << endl;
        // return true; 
    //}

    stockBall.push_back(nouvelle);
    return false;
};