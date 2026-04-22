#include <iostream> 
#include <cmath>
using namespace std;

#include "tools.h"

bool Carre::intersects(const Carre& other) const {
    return abs(x() - other.x()) < (cote_/2 + other.cote_/2) &&
               abs(y() - other.y()) < (cote_/2 + other.cote_/2); 
}


bool Cercle::intersects(const Cercle& other) const {
    double d = sqrt((x() - other.x())*(x() - other.x()) +
                     (y()- other.y())*(y()- other.y()));
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

void Carre::drawFull() const{
    drawSquareFull(x(), y(), cote_, color_); 
}

void Carre::drawEmpty() const{
    drawSquareEmpty(x(), y(), cote_, color_); 
}

void Cercle::drawFull() const{
    Color color = BLACK;
    drawCircleFull(x(), y(), r, color);
}

void Cercle::drawEmpty() const{
    Color color = BLACK;
    drawCircleEmpty(x(), y(), r, color);
}