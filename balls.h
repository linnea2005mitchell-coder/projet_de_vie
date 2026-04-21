#ifndef BALLS_H
#define BALLS_H

#include <vector>
#include "tools.h"

class Ball {
public: 
    Ball(double x, double y, double r, double dx, double dy)
    : corps_(x, y, r), del(dx,dy) {};

    const Cercle& corps() const { return corps_;}
    bool intersects(const Cercle& other) {return corps_.intersects(other); }
    bool intersects(const Carre& c) {return corps_.intersects(c); }

    void drawBall() const;
    
protected :
    Cercle corps_;
    Delta del;
};

bool verif_ball(double x, double y, double r, double dx, double dy, 
                std::vector<Ball>& stockBall);
bool verif_delta(double dx, double dy);

#endif