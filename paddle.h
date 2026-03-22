#include <iostream> 
#include "tools.h"


bool verif_paddle(const double& x,const double& y,const double& r); 

class Paddle : public Cercle {
public: 
using Cercle::intersects;
    Paddle(double x, double y, double r, 0.0, double 0.0 ) // pas sure du dx,dy
    : Cercle(x, y, r, dx, 0) {}
 //ajouter un compteur pour transmettre les index au fonction de collisions
private :
};