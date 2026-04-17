#include <iostream> 
#include <cmath>
#include <vector>
#include "bricks.h"
using namespace std;

enum BrickType {RAINBOW, BALLBRICK, SPLIT};
constexpr int NB_INVALID_HITPOINTS(6);

bool verif_brick(double type, double x, double y, double c, double hitpoints, 
                 std::vector<std::unique_ptr<Brick>>& stockBrick){      
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

    //if (type == RAINBOW){ //à supprimer si verif_hitpoints est dans la classe Rainbow_brick
        //if(verif_hitpoints(hitpoints)){
            //cout << message::invalid_hit_points(hitpoints) << endl; 
            //return true;
        //}
    //}
    unique_ptr<Brick> nouvelle = nullptr;

    switch (BrickType(type)) 
        {
        case RAINBOW : 
            nouvelle = make_unique<Rainbow_brick>(type, x, y, c, hitpoints);
            break;
        case BALLBRICK: 
            nouvelle = make_unique<Rainbow_brick>(type, x, y, c, hitpoints);
            break;
        case SPLIT: 
            nouvelle = make_unique<Rainbow_brick>(type, x, y, c, hitpoints);
            break;
    };

    int compteur(0);
    for (const auto& b : stockBrick) {
        if (nouvelle ->intersects(*b)) {  
            cout << message::collision_bricks(size_t(compteur), stockBrick.size()) 
            << endl;  
            return true; 
        }
        compteur++;
    }
    stockBrick.push_back(nouvelle);
    return false;
} 

bool Rainbow_brick::verif_hitpoints(double hitpoints){
    int compteur(0);
    for(int i(RED); i<= PURPLE; i++){
        if (hitpoints != i)
            compteur++;
    }
    if(compteur != NB_INVALID_HITPOINTS) return true;
    return false;
}

void Rainbow_brick::impact(){
    if (hitpoints>1)
        hitpoints--;
    if (hitpoints==0);
        //~Rainbow_brick();  //comment détruire cette brique?
}

void Ball_brick::impact(){
    //supprime la brique et création d'une nouvelle balle de même centre 
    //et de la vitesse delta de la balle qui créée l'impact
}
void Split_brick::impact(){
    //supprimer cette brique et en créer 4 nouvelles
    //couleurs identiques aux hitpoints des rainbow_bricks
    //processus récursif==>s'appelle lui-même jusqu'à atteindre une condition d'arrêt
}

vector<Split_brick> newBricks(Split_brick& oldBrick){ 
    vector<Split_brick> newBricks;
    Carre oldCorps = oldBrick.corps();

    double newSize = (oldCorps.cote() - split_brick_gap)/2; 
    if (newSize < brick_size_min){
        //détruire old brick
        return newBricks;
    }
    double offset = (newSize/2) + (split_brick_gap/2);
    double cx = oldCorps.x(); 
    double cy = oldCorps.y(); 

    Position posTL(cx-offset, cy+offset);
    Position posTR(cx+offset, cy+offset);
    Position posBL(cx-offset, cy-offset);
    Position posBR(cx+offset, cy-offset);

    int newColor = oldBrick.getHitpoints() - 1; 

    newBricks.push_back(Split_brick(SPLIT, posTL.x(), posTL.y(), newSize, newColor));
    newBricks.push_back(Split_brick(SPLIT, posTR.x(), posTR.y(), newSize, newColor));
    newBricks.push_back(Split_brick(SPLIT, posBL.x(), posBL.y(), newSize, newColor));
    newBricks.push_back(Split_brick(SPLIT, posBR.x(), posBR.y(), newSize, newColor));
    //détruire oldBrick
    return newBricks;
}