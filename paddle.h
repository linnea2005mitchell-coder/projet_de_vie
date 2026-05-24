#ifndef PADDLE_H
#define PADDLE_H

#include "tools.h" 

class Paddle {
public: 
    Paddle() : corps_(0, -1, 5), delta_ (0,0) {}
    Paddle(double x, double y, double r)
        : corps_ (x, y, r), delta_ (0,0) {}
    const Cercle& corps() const { return corps_;}
    Delta& delta() { return delta_;}
    void set_x(double new_x) { corps_.set_x(new_x); }
    void set_y(double new_y) { corps_.set_y(new_y); }
    void set_delta(double d) { delta_.set_dx(d); }

    void drawPaddle() const;
 
protected:
    Cercle corps_;
    Delta delta_;
};

bool verif_paddle(double x, double y, double r, Paddle& pad, double k); 

#endif