#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>  //à enlever après
#include <cmath>
#include <algorithm>
#include "constants.h"

void verif_delta(double& dx, double& dy);

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


class Cercle : public Position, public Delta {
public : 
    Cercle(double x, double y, double r, double dx, double dy) 
        : Position (x, y), Delta (dx,dy), r(r) {}

protected :
    double r;

    bool intersects(const Cercle& other) const { // rend true s'il y a intersection
        double d = sqrt((cx - other.cx)*(cx - other.cx) +
                     (cy - other.cy)*(cy - other.cy));
        return d < (r + other.r); // ici faire diff lors des test entre paddle et ball
        }
    bool intersects(const Carre& c) const { // rend true s'il y a intersection
    
        double half = c.cote() / 2.0;
        double cx = c.x();
        double cy = c.y();
        double closestX = std::max(cx - half, std::min(x(), cx + half));
        double closestY = std::max(cy - half, std::min(y(), cy + half));
        double dx = x() - closestX;
        double dy = y() - closestY;

        return (dx*dx + dy*dy) < (r*r);
        };
};


class Carre : public Position {
public : 
    // ajouter compteur pour pouvoir le transmettre au fonction de collisions
    Carre(double x, double y, double c) 
        : Position (x, y), cote_(c) {}
    
    Position::x;
    Position::y;
    double cote() const {return cote_; };

    bool intersects(const Carre& other) const { // rend true s'il y a intersection
        return abs(cx - other.cx) < (cote_/2 + other.cote_/2) &&
               abs(cy - other.cy) < (cote_/2 + other.cote_/2); }

protected :
    double cote_;
    
};

#endif