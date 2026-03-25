#ifndef PADDLE_H
#define PADDLE_H

#include "tools.h" 


bool verif_paddle(const double& x,const double& y,const double& r); 

class Paddle : public Cercle {
public: 
using Cercle::intersects;
    Paddle(double x, double y, double r)
    : Cercle(x, y, r) {}
 
private :;
};

#endif