#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
#include <algorithm>
#include "constants.h"
#include "message.h"

class Position {
public: 
    Position(double x, double y) 
       : cx(x), cy(y) {}
    double x() const {return cx ;}
    double y() const {return cy ;}

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


class Carre {
public : 
    Carre(double x, double y, double c) 
        : cote_(c), pos(x,y) {}
    
    double cote() const {return cote_; };
    double x() const {return pos.x(); }
    double y() const {return pos.y(); }
    bool intersects(const Carre& other) const;
       
protected :
    double cote_;
    Position pos;
};


class Cercle {
public : 
    Cercle(double x, double y, double ray) 
        : pos(x, y), r(ray) {}
    double x() const {return pos.x(); }
    double y() const {return pos.y(); }

protected :
    double r;
    Position pos;

    bool intersects(const Cercle& other) const;
    bool intersects(const Carre& c) const;
};

#endif
