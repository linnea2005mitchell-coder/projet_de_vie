#include <iostream>
#include <string>
#include "lecture.h"
using namespace std;


int main(int argc, char* argv[]){
    if(argc>1)
        lectureFichier(argv[1]);
    
    return 0;
}

