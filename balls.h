#ifndef BALLS_H
#define BALLS_H

#include <vector>
#include "tools.h"

class Ball {
public: 
    Ball(double x, double y, double r, double dx, double dy)
    : corp(x, y, r), del(dx,dy) {};
 
private :
Cercle corp;
Delta del;
};

bool verif_ball(double x, double y, double r, double dx, double dy, 
                std::vector<Ball>& stockBall);
bool verif_delta(double dx, double dy);

#endif