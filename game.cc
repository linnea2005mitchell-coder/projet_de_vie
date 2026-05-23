#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include "game.h"
#include "message.h"
using namespace std;
 
enum EtatLecture {SCORE, LIVES, PADDLE, NB_BRICKS, BRICKS, NB_BALLS, BALLS};
constexpr size_t NB_VAL_PAD(3); 
constexpr size_t NB_VAL_BRICK(4);
constexpr size_t NB_VAL_BALL(5);
constexpr double VITESSE_MAX_PAD(3.0); 
static unsigned etat(0);

bool lecture_fichier(const string& nomFichier, Game& game){ 
    etat = SCORE;
    ifstream fichier(nomFichier); 
    if(fichier.fail()){
        return false; 
    }

    int compteur(0);
    string line;
    vector<double> tabVal;

    while(getline(fichier >> ws, line)){
        if(line[0]=='#') continue; 
        istringstream data(line);
        if(lecture_ligne(data, tabVal, compteur, game)){
            game.clear();
            return false;
        }
    }
    cout << message::success() << endl;
    return true;
}

bool lecture_ligne(istringstream& data, vector<double>& tabVal, int& compteur, 
                   Game& game){
    double valeur(0);
    while(data>>valeur){ 
        switch(etat){
            case SCORE:
            case LIVES: if(verif_ligne(valeur, tabVal, game)) return true; 
                break; 
            case PADDLE: 
                if(tabVal.size() != NB_VAL_PAD) tabVal.push_back(valeur);
                if(tabVal.size() == NB_VAL_PAD){
                    if(verif_ligne(valeur, tabVal, game)) return true; 
                }
                break;
            case NB_BRICKS:
            case NB_BALLS: compteur = valeur; 
                etat++; break;
            case BRICKS:
                if (lecture_brick(valeur, compteur, tabVal, game)) return true; 
                break;
            case BALLS: 
                if(compteur>0){
                    if(tabVal.size() < NB_VAL_BALL) tabVal.push_back(valeur);
                    if(tabVal.size()==NB_VAL_BALL){
                        compteur--;
                        if(verif_ligne(valeur, tabVal, game)) return true;
                    }
                }
                break;
            default: break;
        }
    }
    return false;
}

bool verif_ligne(int valeur, vector <double>& tabVal, Game& game){ 
    switch(etat){
        case SCORE: 
            etat++;
            if(verif_score(valeur, game.score())) return true;
            break;
	    case LIVES:
            etat++;
            if(verif_lives(valeur, game.lives())) return true;
            break;
        case PADDLE:
            etat++;
            if(verif_paddle(tabVal[0], tabVal[1], tabVal[2], game.pad())){
                cout << message::paddle_outside(tabVal[0], tabVal[1]) << endl;
                return true;
            }
            tabVal.clear();	break;
        case BRICKS:
            if(verif_brick(tabVal[0], tabVal[1], tabVal[2], tabVal[3], tabVal[4], 
               game.stockBrick()) or intersects_brick_paddle(game)) return true;   
            tabVal.clear();	break;
        case BALLS:
            if(verif_ball(tabVal[0], tabVal[1], tabVal[2], tabVal[3], tabVal[4], 
               game.stockBall()) or intersects_ball_brick(game) 
               or intersects_paddle_ball(game)) return true;
            tabVal.clear(); break;
	    default: 
            break;  
    }
    return false;
}

bool lecture_brick(double valeur, int& compteur, vector<double>& tabVal, Game& game){
    if(compteur>0){
        if(tabVal.size() < NB_VAL_BRICK) tabVal.push_back(valeur);
        else if(tabVal.size()==NB_VAL_BRICK && tabVal[0]==0){
            compteur--;
            tabVal.push_back(valeur);
            if(verif_ligne(valeur, tabVal, game)) return true; 
        }
        if(tabVal.size()==NB_VAL_BRICK && tabVal[0]!=0){
            compteur--;
            tabVal.push_back(1); 
            if(verif_ligne(valeur, tabVal, game)) return true; 
        }
    }
    if(compteur==0) etat++; 
    return false;
}

bool verif_score(int& score, int& scoreGame){ 
    if (score<0){
        cout << message::invalid_score(score)<< endl;
        return true;
    }
    scoreGame = score;
    return false;
}

bool verif_lives(int& live, int& liveGame){
    if (live<0){
        cout<< message::invalid_lives(live)<< endl;
        return true;
    }
    liveGame = live;
    return false;
}

bool intersects_brick_paddle(Game& game){ 
    if (game.pad().corps().intersects((*game.stockBrick().back()).corps())) {
        cout << message::collision_paddle_brick
        (game.stockBrick().size()-1) << endl;
        return true; 
    }
    return false;
}

bool intersects_ball_brick(Game& game){ 
    int k(0);
    Ball derniere = game.stockBall().back(); 
    for (const auto& brick : game.stockBrick()) {
        if (derniere.intersects((*brick).corps())) {  
            cout << message::collision_ball_brick
            (game.stockBall().size()-1, size_t(k)) << endl;
            return true; 
        }
        k++;
    }
    return false;
}

bool intersects_paddle_ball(Game& game){
    Ball derniere = game.stockBall().back();
    if (derniere.intersects(game.pad().corps())) {
        cout << message::collision_paddle_ball(game.stockBall().size()-1) << endl;
        return true; 
    }
    return false;
}

void ecriture_fichier(const string& path, Game& game){
    ofstream file(path);
    
    file << "# score" << endl;
    file << game.score() << endl << endl;

    file << "# lives" << endl;
    file << game.lives() << endl << endl;

    file << "# paddle" << endl;
    file << game.pad().corps().x() << " " << game.pad().corps().y() 
         << " " << game.pad().corps().r() << endl << endl;

    file << "# bricks" << endl;
    file << game.stockBrick().size() << endl; 

    for (const auto& brick : game.stockBrick()) {
        if (brick){
            file << brick->type() << " " << brick->corps().x() << " " 
                 << brick->corps().y() << " " << brick->corps().cote() ; 
                 
            if (brick->type() == 0){ 
                int hitpoints=static_cast<int>(brick->corps().color());
                ++hitpoints;
                file << " " << hitpoints;  
            }
            file << endl; 
        }
    }
    file << endl;

    file << "# balls" << endl;
    file << game.stockBall().size() << endl; 

    for (const auto& ball : game.stockBall()) {
            file << ball.corps().x() << " " << ball.corps().y() << " " 
            << ball.corps().r() << " " << ball.dx() << " " << ball.dy() << endl;
    }
    file << endl; 
}
  
void Game::drawGame(){
    if(correctFile_){
        drawSquareEmpty(0, 0, arena_size, GREY);
        pad_.drawPaddle();
        for(auto& p : stockBrick()){
            p->drawBrick();
        }
        for(auto& p : stockBall()){
            p.drawBall();
        }
    }
}

void Game::clear(){
    stockBrick_.clear();
    stockBall_.clear();
    score_ = 0;
    lives_ = 0;
}

void Game::updatePad(){
    double dist_diff = mouseX_ - pad_.corps().x() + epsil_zero; 
    double oldPad = pad_.corps().x();

    if (dist_diff > VITESSE_MAX_PAD){ 
        double newX = pad_.corps().x() + VITESSE_MAX_PAD;
        pad_.set_delta(newX - pad_.corps().x());
        pad_.set_x(newX);
    }
    else if (dist_diff < -VITESSE_MAX_PAD){
        double newX = pad_.corps().x() - VITESSE_MAX_PAD;
        pad_.set_delta(newX - pad_.corps().x());
        pad_.set_x(newX);
    }
    else{
        pad_.set_delta(mouseX_ - pad_.corps().x());
        pad_.set_x(mouseX_);
    }

    for(auto& brick : stockBrick_){
        if(pad_.corps().intersects((*brick).corps()))
            pad_.set_x(oldPad);
        }
     
    if(verif_paddle(pad_.corps().x(), pad_.corps().y(), pad_.corps().r(), pad_))
        pad_.set_x(oldPad);
}

void Game::collision_brick(int index, double dx, double dy){
    if ((*stockBrick_[index]).type() == 0){ //rainbow_brick
        if((*stockBrick_[index]).collision()){
            stockBrick_.erase(stockBrick_.begin() + index);
        }
    }
    else if ((*stockBrick_[index]).type() == 1){ //ball_brick
        Ball new_ball((*stockBrick_[index]).corps().x(), 
                      (*stockBrick_[index]).corps().y(), new_ball_radius, dx, dy);
        stockBall_.push_back(new_ball);
        stockBrick_.erase(stockBrick_.begin() + index);
    }
    else{ //split_brick
        Split_brick* oldBrick = dynamic_cast<Split_brick*>(stockBrick_[index].get()); //pk .get()?, faut il delete ce pointeur du coup?, revoir suppression
        if(oldBrick){
            vector<unique_ptr<Split_brick>> newBricks = oldBrick->newBricks();
            for(auto& i : newBricks){
                i->collision();
                stockBrick_.push_back(unique_ptr<Split_brick>(std::move(i)));
            }
        }
        stockBrick_.erase(stockBrick_.begin() + index);
    }
}

void Game::updateBalls(){

    int compteur(0);
     for (auto& ball_1 : stockBall()) {
        int rebonds(0);
        Position ancienne(ball_1.corps().x(),ball_1.corps().y());

        ball_1.set_x(ball_1.corps().x() + ball_1.dx());
        ball_1.set_y(ball_1.corps().y() + ball_1.dy());

        if(ball_1.corps().y() < epsil_zero){ // si dehors (checker corrdonnées)
             stockBall_.erase(stockBall_.begin() + compteur);
        }

        while(collision(ball_1)){
            rebonds++; 
            ball_1.set_x(ancienne.x());
            ball_1.set_y(ancienne.y());
            if (rebonds < nb_bounce_max){ // check delta max 
                double delta_norm(sqrt(ball_1.dx()*ball_1.dx() + ball_1.dy()*ball_1.dy()));
                if (delta_norm > delta_norm_max - epsil_zero){
                    ball_1.delta() = ball_1.delta()*(delta_norm_max/delta_norm);
                }

                ball_1.set_x(ball_1.corps().x() + ball_1.dx());
                ball_1.set_y(ball_1.corps().y() + ball_1.dy());
            }
            else break; 
        }
        compteur++;
    }
}
bool Game::collision(Ball& a){ 

    double ax(a.corps().x());
    double ay(a.corps().y());
 
        for (auto& b : stockBall()) {
            if (&a == &b) {
                continue;
            }
            if (a.intersects(b.corps())){ //ajouter epsil zero
        
                
                Delta pulse_1(impulsion(a.corps(), a.delta(), b.corps(), b.delta()));
                a.delta() += pulse_1;
                return true;
            }
        }

        int compteur(0);
        for (const auto& brick : stockBrick()) {
            if (a.intersects(brick->corps())) { //ajouter epsil zero
                double by(brick->corps().y());
                double half(brick->corps().cote()/2);

                if (abs(by -ay -a.dx())<half){ //touche un coté
                    a.set_dx(-a.dx());
                }
                else{ //touche en haut ou en bas
                    a.set_dy(-a.dy());
                }

                collision_brick(compteur, a.dx(), a.dy());// appel foncton casse brique 
                
                return true;
            }
            compteur++;
        }

        if (a.intersects(pad().corps())) { //ajouter epsil zero
                
                Delta pulse_1(impulsion(a.corps(), a.delta(), pad_.corps(), pad_.delta()));
                a.delta() += pulse_1;
        
                return true;
        }

        if (ax- a.corps().r()  < epsil_zero 
        || ax + a.corps().r() > arena_size - epsil_zero) { //rebond  bord
            a.set_dx(-a.dx());
            return true;
        }

        if(ay + a.corps().r() > arena_size - epsil_zero){ //rebond plafond
            a.set_dy(-a.dy());
            return true;
        }
        return false;
    }
