#ifndef PADDLE_H
#define PADDLE_H

#include "tools.h" 

class Paddle {
public: 
    Paddle() : corps_(0, -1, 5) {}
    Paddle(double x, double y, double r)
    : corps_ (x, y, r) {}
    const Cercle& corps() const { return corps_;}
    void set_x(double new_x) { corps_.set_x(new_x); }
    void set_y(double new_y) { corps_.set_y(new_y); }
    
    void drawPaddle() const;
 
protected :
    Cercle corps_;
};

bool verif_paddle(double x, double y, double r, Paddle& pad); 

#endif