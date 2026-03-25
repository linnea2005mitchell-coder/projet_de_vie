#ifndef BRICKS_H
#define BRICKS_H
//#include "tools.h" 

class Brick : public Carre{
public:
    Brick(double t, double x, double y, double c, double h) 
        : Carre(x, y, c), type(t), hitpoints(h){} 

    ~Brick(){} //destructeur spécifique de brick, ensuite celui de Carre (doit être virtual) sera appelé 
    
    double getType(){return type; }
    double getHitpoints(){return hitpoints; }

private: 
    double type, hitpoints;                                                                                                                                                                                                                                                                                                                                                     
};

bool verif_bricks(const double& type, const double& x, const double& y, 
                  const double& c, const double& hitpoints);

bool verif_hitpoints(const double& hitpoints);
#endif 