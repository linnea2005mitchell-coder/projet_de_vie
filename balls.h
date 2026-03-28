#ifndef BALLS_H
#define BALLS_H

#include <vector>
#include "tools.h"

class Ball : public Cercle, public Delta {
public: 
    using Cercle::intersects;
    using Delta::Delta;
    Ball(double x, double y, double r, double dx, double dy)
    : Cercle(x, y, r), Delta(dx,dy) {};
 
private :;
};

bool verif_ball(double x, double y, double r, double dx, double dy, 
                std::vector<Ball>& stockBall);
bool verif_delta(double dx, double dy);

#endif