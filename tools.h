#include <iostream> 
#include <cmath>
#include "constants.h"

bool verif_delta(double& dx, double& dy);

class Position {
public: 
    Position(double x, double y) 
       : cx(x), cy(y) {}
    
protected: 
    double cx,cy;
};


class Delta {
    public: 
    Delta(double x, double y) 
    : dx(x), dy(y) {}
    
protected: 
    double dx, dy;
};


class Cercle : public Position, public Delta {
public : 
    Cercle(double x, double y, double r, double dx, double dy) 
        : Position (x, y), Delta (dx,dy), r(r) {}

protected :
    double r;

    bool intersects(const Cercle& other)  {
        double d = sqrt((cx - other.cx)*(cx - other.cx) +
                     (cy - other.cy)*(cy - other.cy));
        return d < (r + other.r); // ici faire diff lors des test entre paddle et ball
        }
    bool intersects(const Carre& other) {

    }
// ajouter intersection cercle brique 

};


class Carre : public Position {
public : 
    // ajouter compteur pour pouvoir le transmettre au fonction de collisions
    Carre(double x, double y, double c) 
        : Position (x, y), cote(c) {}
    
    double cote() const {return cote; };

    bool intersects(const Carre& other) const {
        return abs(cx - other.cx) < (cote + other.cote/2) &&
               abs(cy - other.cy) < (cote + other.cote/2); }

protected :
    double cote;
    
};


