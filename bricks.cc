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
    if (type == RAINBOW){ //vérifier que verif_hitpoints fonctionne bien
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
    stockBrick.push_back(std::move(nouvelle));
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

vector<unique_ptr<Split_brick>> Split_brick::newBricks() const{ 
    vector<unique_ptr<Split_brick>> newBricks;
    double newSize = (corps_.cote() - split_brick_gap)/2;

    if (newSize >= brick_size_min) {
        double offset = (corps_.cote() + split_brick_gap)/4;

        Position posTL(corps_.x() - offset, corps_.y() + offset);
        Position posTR(corps_.x() + offset, corps_.y() + offset);
        Position posBL(corps_.x() - offset, corps_.y() - offset);
        Position posBR(corps_.x() + offset, corps_.y() - offset);

        int index = static_cast<int>(corps_.color());
        index++; 
        Color newColor = static_cast<Color>(index);

        newBricks.push_back(make_unique<Split_brick>(SPLIT, posTL.x(), posTL.y(), 
                                                     newSize, newColor));
        newBricks.push_back(make_unique<Split_brick>(SPLIT, posTR.x(), posTR.y(), 
                                                     newSize, newColor));
        newBricks.push_back(make_unique<Split_brick>(SPLIT, posBL.x(), posBL.y(), 
                                                     newSize, newColor));
        newBricks.push_back(make_unique<Split_brick>(SPLIT, posBR.x(), posBR.y(), 
                                                     newSize, newColor));
    
        return newBricks;
    }
    return newBricks;
}

void Brick::drawBrick() const{
    corps_.drawFull();
}

void Ball_brick::drawBrick() const{
    corps_.drawFull();
    drawCircleFull(corps().x(), corps().y(), new_ball_radius, BLACK);
}

void Split_brick::drawBrick() const {
    corps_.drawFull();

    vector<unique_ptr<Split_brick>> newBricksTab = this->newBricks(); 
    if (newBricksTab.size()>0) {
        for (auto& b : newBricksTab){
            b->drawBrick();
        }
    }
}

