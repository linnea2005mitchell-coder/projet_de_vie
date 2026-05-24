#include <iostream> 
#include <cmath>
#include "tools.h"

using namespace std;

bool Carre::intersects(const Carre& other) const {
    return abs(x() - other.x()) < (cote_/2 + other.cote_/2) &&
           abs(y() - other.y()) < (cote_/2 + other.cote_/2); 
}


bool Cercle::intersects(const Cercle& other, const double k) const {//k=epsil_zero ou 0
    double d = sqrt((x() - other.x())*(x() - other.x()) +
                    (y()- other.y())*(y()- other.y()));
    return d < (r() + other.r() + k);
}

bool Cercle::intersects(const Carre& c, const double k) const { //k=epsil_zero ou 0
    double half = c.cote() / 2.0;
    double cx = c.x();
    double cy = c.y();
    double closestX = max(cx - half, min(x(), cx + half));
    double closestY = max(cy - half, min(y(), cy + half));
    double dx = x() - closestX;
    double dy = y() - closestY;

    return (dx*dx + dy*dy) < (r()*r() + k); 
}

void Carre::drawFull() const{
    drawSquareFull(x(), y(), cote_, color_); 
}

void Carre::drawEmpty() const{
    drawSquareEmpty(x(), y(), cote_, color_); 
}

void Cercle::drawFull() const{
    Color color = BLACK;
    drawCircleFull(x(), y(), r(), color );
}

void Cercle::drawEmpty() const{
    Color color = BLACK;
    drawCircleEmpty(x(), y(), r(), color );
}

void Delta::operator+=(Delta autre){
    dx_ += autre.dx();
    dy_ += autre.dy();
}
Delta Delta::operator-(Delta autre){
    Delta resultat(dx_ - autre.dx(), dy_ - autre.dy());
    return resultat;
}

Delta Delta::operator*(double coef){

     Delta resultat(dx_ * coef, dy_ * coef);
    return resultat;
}

double Delta::operator*(Delta autre){
    return dx_*autre.dx() + dy_*autre.dy();
}

Delta impulsion(const Cercle& a, Delta& da, const Cercle& b,  Delta& db){

    double diff_x(b.x() - a.x()); 
    double diff_y(b.y() - a.y()); 
    Delta vect_ab(diff_x, diff_y);
    Delta vect_ba(-diff_x, -diff_y);
    
    double coef_a = (vect_ab*da)/(diff_x*diff_x + diff_y*diff_y); 
    Delta vn_a = vect_ab*coef_a;

    double coef_b = (vect_ba*db)/(diff_x*diff_x + diff_y*diff_y); 
    Delta vn_b = vect_ba*coef_b;

     double coef_r;
    if (b.y() < epsil_zero) { // if b = pad
        coef_r = 2; //(2 infini**2) / (r_a + infini**2) = 2
    }// ça fait un comportement un peu bizarre par moment je trouve 
    // mais j'ai vraiment appliqué les explications des données donc je vois pas pourquoi ce serait faux 
    else {
        coef_r = (2*b.r()*b.r()/(a.r()*a.r() + b.r()*b.r())); 
    }
    Delta pulse = (vn_b - vn_a)*coef_r;

    return pulse;
}