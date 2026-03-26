#ifndef BALLS_H
#define BALLS_H

#include <vector>
#include "tools.h"
#include "paddle.h"
#include "bricks.h"

class Ball : public Cercle, public Delta {
public: 
    using Cercle::intersects;
    using Delta::Delta;
    Ball(double x, double y, double r, double dx, double dy)
    : Cercle(x, y, r), Delta(dx,dy) {};
 
private :;
};

bool verif_balls(double& x, double& y, double& r, double& dx, double& dy, Game& game);

#endif