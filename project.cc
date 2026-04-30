#include <iostream>
#include <string>
#include <gtkmm/application.h>
#include "game.h"
#include "gui.h"
using namespace std;


int main(int argc, char* argv[]){
    Game game( 0, 0, {}, {}, {});
    string file_name("");

    if(argc>1){
        file_name = argv[1];
    }

    auto app = Gtk::Application::create();
    return app->make_window_and_run<My_window>(1, argv, file_name, std::move(game)); 

    return 0;
}

