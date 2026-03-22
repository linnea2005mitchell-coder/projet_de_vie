// message philosophique: saute dans une flaque avant que la flaque te saute
#include <vector>
#include "tools.h"

bool verif_balls(int& x, int& y, int& r, int& dx, int& dy);

class Ball : public Cercle {
public: 
    using Cercle::intersects;
    Ball(double x, double y, double r, double dx, double dy)
    : Cercle(x, y, r, dx, dy) {}
 //ajouter un compteur pour transmettre les index au fonction de collisions
private :
};

vector<Ball> stock; 
