#ifndef BRICKS_H
#define BRICKS_H
//#include "tools.h" 

//A SUPPRIMER UNE FOIS QUE TOOLS.H EST INCLU:
class Position {
public: 
    Position(double x, double y) 
       : cx(x), cy(y) {}
    double x() const {return cx ;}
    double y() const {return cy ;}

protected: 
    double cx,cy;
};

class Carre : public Position {
public : 
    Carre(double x, double y, double c) 
        : Position (x, y), cote_(c) {}
    
    //using Position::x; //à quoi ça sert?
    //using Position::y;
    double cote() const {return cote_; };

    bool intersects(const Carre& other) const { // rend true s'il y a intersection
        return abs(cx - other.cx) < (cote_/2 + other.cote_/2) &&
               abs(cy - other.cy) < (cote_/2 + other.cote_/2); }

    virtual ~Carre(){}

protected :
    double cote_;
    
};

// FIN SUPPRESSION

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