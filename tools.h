#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
#include <algorithm>
#include "constants.h"
#include "message.h"

bool verif_delta(const double& dx, const double& dy);
bool verif_outside(const double& x, const double& y, const double& d);


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


class Carre : public Position {
public : 
    using Position::x;
    Carre(double x, double y, double c) 
        : Position (x, y), cote_(c) {}
    
    double cote() const {return cote_; };
    bool intersects(const Carre& other) const; // rend true s'il y a intersection
       
protected :
    double cote_;
    virtual ~Carre() {}
};


class Cercle : public Position {
public : 
    Cercle(double x, double y, double ray) 
        : Position (x, y), r(ray) {}

protected :
    double r;

    bool intersects(const Cercle& other) const;
    bool intersects(const Carre& c) const;

};

#endif