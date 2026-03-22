#include <iostream> 
#include "tools.h"


bool verif_paddle(const double& x,const double& y,const double& r); 

class Paddle : public Cercle {
public: 
    Paddle(double x, double y, double r, double dx, double dy) // pas sure du dx,dy
    : Cercle(x, y, r, dx, 0) {}
 //ajouter un compteur pour transmettre les index au fonction de collisions
private :
};