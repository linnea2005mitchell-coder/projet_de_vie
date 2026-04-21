#ifndef BRICKS_H
#define BRICKS_H
#include "tools.h" 
#include <vector>
#include <memory>

class Brick {
public:
    Brick(double t, double x, double y, double c, double h) 
        : corps_(x, y, c), type(t), hitpoints(h){} //mettre hitpoints ici ou comme attribut spécifique à Rainbow_brick?

    ~Brick() = default; //revoir
    double getType(){return type; }
    double getHitpoints(){return hitpoints; }
    const Carre& corps() const { return corps_;} //plutôt faire fonctions pour avoir directemetn x, y, t? ouai c'est un peu long ik mais les methodes intersects fonctionnent avec cercle ou carré comme param dcp j'ai trouvé + simple mais c'est #relou
    bool intersects(const Brick& other) const {return corps_.intersects(other.corps());};

protected: 
    Carre corps_;
    double type, hitpoints; 
};

class Rainbow_brick : public Brick{
    using Brick::intersects;
public:
    Rainbow_brick(double t, double x, double y, double c, double h)
        : Brick(t, x, y, c, h){ 
            if(!verif_hitpoints(h))
                hitpoints=h;
            }
    ~Rainbow_brick() = default; //revoir

    bool verif_hitpoints(double hitpoints);
    void impact();

private:
    double hitpoints;
};

class Ball_brick : public Brick{
    using Brick::intersects;
public:
    Ball_brick(double t, double x, double y, double c, double h)
        : Brick(t, x, y, c, h){}
    ~Ball_brick() = default; //revoir

    void impact();

private:
    //a une balle?
};

class Split_brick : public Brick{
    using Brick::intersects;
public:
    Split_brick(double t, double x, double y, double c, double h)
        : Brick(t, x, y, c, h){}
    ~Split_brick() = default; //revoir

    void impact();
    std::vector<Split_brick> newBricks(Split_brick& oldBrick); //voir comment faire avec ce tableau et/ou tableau stockBricks
private:
};

bool verif_brick(double type, double x, double y, double c, double hitpoints, 
                 std::vector<std::unique_ptr<Brick>>& stockBrick);
//bool verif_hitpoints(double hitpoints); //à supprimer si c'est dans la classe rainbow_brick
#endif 