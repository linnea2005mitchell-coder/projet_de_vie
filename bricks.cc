#include <iostream> 
#include <cmath>
#include <vector>
#include "bricks.h"
using namespace std;

enum BrickType {RAINBOW, BALLBRICK, SPLIT};
constexpr int NB_INVALID_HITPOINTS(6);

bool verif_brick(double type, double x, double y, double c, double hitpoints, 
                 vector<unique_ptr<Brick>>& stockBrick){      
    if ((type != RAINBOW) && (type != BALLBRICK) && (type != SPLIT)){
        cout << message::invalid_brick_type(type) << endl; 
        return true;
    }              
    double halfC = c / 2.0;
    if ((x-halfC) < 0 || (y-halfC) < 0 || (x+halfC) > arena_size 
        || (y+halfC) > arena_size) { 
        cout << message::brick_outside(x, y) << endl; 
        return true;
    }
    if (c < brick_size_min){
        cout << message::invalid_brick_size(c) << endl;
        return true;
    }

    hitpoints--;
    if (type == RAINBOW){
        if(verif_hitpoints(hitpoints)) return true;
    }
    Color color = static_cast<Color>(hitpoints);

    unique_ptr<Brick> nouvelle = nullptr;
    switch (BrickType(type)) 
        {
        case RAINBOW : 
            nouvelle = make_unique<Rainbow_brick>(type, x, y, c, color);
            break;
        case BALLBRICK: 
            nouvelle = make_unique<Ball_brick>(type, x, y, c, color);
            break;
        case SPLIT: 
            nouvelle = make_unique<Split_brick>(type, x, y, c, color);
            break;
    };
    if(verif_intersect(stockBrick, nouvelle)) return true;
   
    return false;
} 

bool verif_intersect(vector<unique_ptr<Brick>>& stockBrick, 
                     unique_ptr<Brick>& nouvelle){
    int compteur(0);
    for (const auto& b : stockBrick) {
        if (nouvelle ->intersects(*b)) {  
            cout << message::collision_bricks(size_t(compteur), stockBrick.size()) 
                 << endl;  
            return true; 
        }
        compteur++;
    }
    stockBrick.push_back(std::move(nouvelle)); //c'est quoi move?
    return false;
}

bool verif_hitpoints(double hitpoints){
    int compteur(0);
    for(int i(RED); i<= PURPLE; i++){
        if (hitpoints != i)
            compteur++;
    }
    if(compteur != NB_INVALID_HITPOINTS){
        cout << message::invalid_hit_points(hitpoints) << endl; 
        return true;
    }
    return false;
}

vector<Carre> Split_brick::newSquares(Carre old) const{
    vector<Carre> newSquares;
    double newSize = (old.cote() - split_brick_gap)/2;

    if (newSize >= brick_size_min) {
        double offset = (old.cote() + split_brick_gap)/4;

        Position posTL(old.x() - offset, old.y() + offset);
        Position posTR(old.x() + offset, old.y() + offset);
        Position posBL(old.x() - offset, old.y() - offset);
        Position posBR(old.x() + offset, old.y() - offset);

        int index = static_cast<int>(old.color());
        index++; 
        Color newColor = static_cast<Color>(index);
        
        newSquares.push_back(Carre(posTL, newSize, newColor));
        newSquares.push_back(Carre(posTR, newSize, newColor));
        newSquares.push_back(Carre(posBL, newSize, newColor));
        newSquares.push_back(Carre(posBR, newSize, newColor));

        return newSquares;
    }
    return newSquares;
}

vector<unique_ptr<Split_brick>> Split_brick::newBricks() const{ 
    vector<unique_ptr<Split_brick>> newBricks;
      
    for(auto& i : newSquares(corps_)){
        newBricks.push_back(make_unique<Split_brick>(SPLIT, i));
    }
    return newBricks;
}

void Rainbow_brick::drawBrick(Carre carre) const{
    carre.drawFull();
}

void Ball_brick::drawBrick(Carre carre) const{
    carre.drawFull();
    drawCircleFull(corps().x(), corps().y(), new_ball_radius, BLACK);
}

void Split_brick::drawBrick(Carre carre) const {
    carre.drawFull();

    for (auto& b : newSquares(carre)){
        b.drawFull();
        drawBrick(b);
    }
}

bool Rainbow_brick::collision(){
    if (hitpoints_>1){
        corps_.set_color(hitpoints_);
        hitpoints_--;
        return false; //=>n'est pas détruite
    }
    return true; //=>doit être détruite
}

bool Ball_brick::collision(){
    return true;
}

bool Split_brick::collision(){
    int color = static_cast<int>(corps_.color());
    color--;
    corps_.set_color(color);
    return true;
}

