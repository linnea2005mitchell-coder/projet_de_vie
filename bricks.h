#ifndef BRICKS_H
#define BRICKS_H
#include "tools.h" 
#include <vector>

class Brick {
public:
    Brick(double t, double x, double y, double c, double h) 
        : corps_(x, y, c), type(t), hitpoints(h){} 

    double getType(){return type; }
    double getHitpoints(){return hitpoints; }
    const Carre& corps() const { return corps_;}
    bool intersects(const Brick& other) const {return corps_.intersects(other.corps());};

protected: 
    Carre corps_;
    double type, hitpoints; 
};

bool verif_brick(double type, double x, double y, double c, double hitpoints, 
                 std::vector<Brick>& stockBrick);
bool verif_hitpoints(double hitpoints);
#endif 