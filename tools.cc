#include <iostream> 
#include <cmath>
using namespace std;

#include "tools.h"

bool verif_delta(const double& dx, const double& dy){
    if (sqrt(dx*dx + dy*dy) > delta_norm_max) {
        cout << message::invalid_delta(dx,dy) << endl;
        return true; }
    return false; 
}

bool verif_outside(const double& x, const double& y, const double& d){
    return ((x-d) < 0) || ((y-d) < 0) || ((x+d) > arena_size) || ((y+d) > arena_size); //true si out
}

bool Carre::intersects(const Carre& other) const {
    return abs(cx - other.cx) < (cote_/2 + other.cote_/2) &&
               abs(cy - other.cy) < (cote_/2 + other.cote_/2); 
}


bool Cercle::intersects(const Cercle& other) const {
    double d = sqrt((x() - other.cx)*(x() - other.cx) +
                     (y()- other.cy)*(y()- other.cy));
    return d < (r + other.r);
}

bool Cercle::intersects(const Carre& c) const {
    double half = c.cote() / 2.0;
    double cx = c.x();
    double cy = c.y();
    double closestX = std::max(cx - half, std::min(x(), cx + half));
    double closestY = std::max(cy - half, std::min(y(), cy + half));
    double dx = x() - closestX;
    double dy = y() - closestY;

    return (dx*dx + dy*dy) < (r*r); // true su intersects 
}