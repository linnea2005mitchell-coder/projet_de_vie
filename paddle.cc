#include <iostream> 
#include "paddle.h"
using namespace std;

bool verif_paddle(double x, double y, double r, Paddle& pad, double k) {
	double a (asin(y/r));
	double x1 (x + cos(a)*r);
	double x2 (x - cos(a)*r);
  	if ((y <= 0) && (y+r > 0) && (x1 >= (0 + k)) && (x2 >= (0 + k)) && 
		(x1 <= (arena_size - k)) && (x2 <= (arena_size - k))) {
		pad = {x,y,r};
		return false ;
	}
	return true;
}

void Paddle::drawPaddle() const{
    corps_.drawEmpty();
}