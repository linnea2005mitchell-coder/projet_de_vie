#ifndef PADDLE_H
#define PADDLE_H

#include "tools.h" 

class Paddle : public Cercle {
public: 
using Cercle::intersects;
    Paddle() : Cercle(0, -1, 5) {}
    Paddle(double x, double y, double r)
    : Cercle(x, y, r) {}
 
private :;
};

bool verif_paddle(double x, double y, double r, Paddle& pad); 

#endif