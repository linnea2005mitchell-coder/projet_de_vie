#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
#include <algorithm>
#include "constants.h"
#include "message.h"
#include "graphic.h"

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
    Carre(double x, double y, double c, Color color) 
        : cote_(c), pos(x,y), color_(color) {}
    
    double cote() const {return cote_; };
    double x() const {return pos.x(); }
    double y() const {return pos.y(); }
    Color color() const {return color_;}
    bool intersects(const Carre& other) const;
    void drawFull() const;
    void drawEmpty() const;
    
protected :
    double cote_;
    Position pos;
    Color color_;
};


class Cercle {
public : 
    Cercle(double x, double y, double ray) 
        :  r_(ray), pos(x, y) {}
    double x() const {return pos.x(); }
    double y() const {return pos.y(); }
    double r() const {return r_; }
    bool intersects(const Cercle& other) const;
    bool intersects(const Carre& c) const;
    void drawFull() const;
    void drawEmpty() const;

protected :
    double r_;
    Position pos;
};

#endif
