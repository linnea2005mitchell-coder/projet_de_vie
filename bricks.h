#ifndef BRICKS_H
#define BRICKS_H
#include "tools.h" 
#include <vector>

class Brick : public Carre{
public:
    Brick(double t, double x, double y, double c, double h) 
        : Carre(x, y, c), type(t), hitpoints(h){} 

    double getType(){return type; }
    double getHitpoints(){return hitpoints; }

private: 
    double type, hitpoints;                                                                                                                                                                                                                                                                                                                                                     
};

bool verif_brick(double type, double x, double y, double c, double hitpoints, 
                 std::vector<Brick>& stockBrick);
bool verif_hitpoints(double hitpoints);
#endif 