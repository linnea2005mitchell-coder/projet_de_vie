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
    void setPos(double x, double y){
        cx = x;
        cy = y;
    }

    void set_x(double nx) { cx = nx; }
    void set_y(double ny) { cy = ny; }

protected: 
    double cx,cy;
};


class Delta {
public: 
    Delta(double x, double y) 
    : dx_(x), dy_(y) {}
    
    const double& dx() const {return dx_ ;}
    const double& dy() const {return dy_ ;}
protected: 
    double dx_, dy_;
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
<<<<<<< HEAD
    void setPos(double x, double y) {pos.setPos(x, y);}
=======

    void set_x(double new_x) { pos.set_x(new_x); }
    void set_y(double new_y) { pos.set_y(new_y); }

>>>>>>> 0948f151fbe6a191a6fbb76652eb48abcbc95b91
    bool intersects(const Cercle& other) const;
    bool intersects(const Carre& c) const;
    void drawFull() const;
    void drawEmpty() const;

protected :
    double r_;
    Position pos;
};

#endif
