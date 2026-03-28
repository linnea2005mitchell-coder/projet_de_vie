#include <iostream> 
#include <cmath>
using namespace std;

#include "tools.h"

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
    double closestX = max(cx - half, min(x(), cx + half));
    double closestY = max(cy - half, min(y(), cy + half));
    double dx = x() - closestX;
    double dy = y() - closestY;

    return (dx*dx + dy*dy) < (r*r); 
}