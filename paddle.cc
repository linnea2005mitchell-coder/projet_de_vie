#include <iostream> 
#include "paddle.h"
using namespace std;

bool verif_paddle(const double& x, const double& y, const double& r, Paddle& pad) {

    double a (asin(y/r));
    double x1 (x + cos(a)*r);
    double x2 (x - cos(a)*r);
     if ((y <= 0) && (y+r > 0) && (x1 >= 0) && (x2 >= 0) && (x1 <= arena_size) && (x2 <= arena_size)) {
      pad = {x,y,r};
      return false ;
     };
   cout << message::paddle_outside(x, y) << endl;
   return true;
}