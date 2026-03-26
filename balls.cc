#include <iostream> 
#include <cmath>
#include <vector>
using namespace std;

#include "balls.h"

bool verif_balls(double& x, double& y, double& r, double& dx, double& dy, Game& game){
    
    if(verif_delta(dx,dy)) return false;

    if (verif_outside(x,y,r)) { 
        cout << message::ball_outside(x,y)<< endl;
        return false;
    };

    Ball nouvelle(x, y, r, dx, dy);
    
    int c(0);
    for (const auto& ball : game.stockBall) {
        if (nouvelle.intersects(ball)) {  //check intersection
            cout << message::collision_balls(size_t(c), game.stockBall.size()) << endl;
            return false; 
        };
        c++;
    };

    int k(0);
    for (const auto& brick : game.stockBrick) {
        if (nouvelle.intersects(brick)) {  //check intersection
            cout << message::collision_ball_brick(size_t(k), game.stockBall.size()) << endl;
            return false; 
        };
        k++;
    };

    if (nouvelle.intersects(game.pad)) {
         cout << message::collision_paddle_ball(game.stockBall.size()) << endl;
         return false; 
    }

    game.stockBall.push_back(nouvelle);
    return true;
};