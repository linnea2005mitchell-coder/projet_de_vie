#include <iostream> 
#include "constants.h"
#include "paddle.h"
using namespace std;

int x,y,r;

bool verif_paddle(int& x, int& y, int& r) {


    double a (asin(y/r));
    double x1 (x + cos(a)*r);
    double x2 (x - cos(a)*r);
     if ((y <= 0) && (y+r > 0) && (x1 >= 0) && (x2 >= 0) && (x1 <= arena_size) && (x2 <= arena_size)) {
        int x,y,r(x,y,r);
        return true ;
     };
     return false;
}