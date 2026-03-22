#include <iostream> 
#include <cmath>
using namespace std;

#include "message.cc"
#include "tools.h"

bool verif_delta(double& dx, double& dy){
    if (sqrt(dx*dx + dy*dy) > delta_norm_max) {
        message::invalid_delta(dx,dy);
        }; 
}