#ifndef BALLS_H
#define BALLS_H

#include <vector>
#include "tools.h"

bool verif_balls(double& x, double& y, double& r, double& dx, double& dy);

class Ball : public Cercle, public Delta {
public: 
    using Cercle::intersects;
    using Delta::Delta;
    Ball(double x, double y, double r, double dx, double dy)
    : Cercle(x, y, r), Delta(dx,dy) {};
 
private :;
};

vector<Ball> stock; 
#endif