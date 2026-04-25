#ifndef BRICKS_H
#define BRICKS_H
#include "tools.h" 
#include <vector>
#include <memory>

class Brick {
public:
    Brick(double t, double x, double y, double c, Color color) 
        : corps_(x, y, c, color), type(t){} 

   virtual ~Brick() = default; //revoir
    double getType(){return type; }
    const Carre& corps() const { return corps_;} 
    bool intersects(const Brick& other) const{return corps_.intersects(other.corps());}
    virtual void drawBrick() const;

protected: 
    Carre corps_;
    double type; 
};

class Rainbow_brick : public Brick{
    using Brick::intersects;
public:
    Rainbow_brick(double t, double x, double y, double c, Color color)
        : Brick(t, x, y, c, color){hitpoints_=static_cast<int>(color);
                                   ++hitpoints_;}
    ~Rainbow_brick() = default; //revoir
    int hitpoints(){return hitpoints_;}

    void impact();

private:
    int hitpoints_;
};

class Ball_brick : public Brick{
    using Brick::intersects;
public:
    Ball_brick(double t, double x, double y, double c, Color color)
        : Brick(t, x, y, c, color){}
    ~Ball_brick() = default; //revoir

    void impact();
    void drawBrick() const;

private:
    
};

class Split_brick : public Brick{
    using Brick::intersects;
public:
    Split_brick(double t, double x, double y, double c, Color color) 
        : Brick(t, x, y, c, color){} 
    ~Split_brick() = default; //revoir

    void impact();
    std::vector<std::unique_ptr<Split_brick>> newBricks() const; //voir comment faire avec ce tableau et/ou tableau stockBricks
    void drawBrick() const;

    
private:
};

bool verif_brick(double type, double x, double y, double c, double hitpoints, 
                 std::vector<std::unique_ptr<Brick>>& stockBrick);
bool verif_intersect(std::vector<std::unique_ptr<Brick>>& stockBrick, 
                     std::unique_ptr<Brick>& nouvelle);
bool verif_hitpoints(double hitpoints); 
#endif 