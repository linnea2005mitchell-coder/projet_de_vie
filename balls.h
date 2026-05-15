#ifndef BALLS_H
#define BALLS_H

#include <vector>
#include "tools.h"

class Ball {
public: 
    Ball(double x, double y, double r, double dx, double dy)
    : corps_(x, y, r), del(dx,dy) {};

    const Cercle& corps() const { return corps_;}
    Delta& delta() { return del;}
    const double& dx() const { return del.dx();}
    const double& dy() const { return del.dy();}

    void set_x(double new_x) { corps_.set_x(new_x); }
    void set_y(double new_y) { corps_.set_y(new_y); }
    void set_dx(double new_dx) { del.set_dx(new_dx); }
    void set_dy(double new_dy) { del.set_dy(new_dy); }

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