#include "graphic.h"
#include "graphic_gui.h"

using namespace std;

static const Cairo::RefPtr<Cairo::Context> *ptcr(nullptr);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context> &cr)
{
    ptcr = &cr;
}

void set_color(Color color)
{
    double r(0.), g(0.), b(0.);

    switch (color)
    {
    case RED:
        r = 1.0;
        break;
    case ORANGE:
        r = 1.0;
        g = 0.5;
        break;
    case YELLOW:
        r = 1.0;
        g = 1.0;
        break;
    case GREEN:
        g = 1.0;
        break;
    case CYAN:
        g = 1.0;
        b = 1.0;
        break;
    case BLUE:
        b = 1.0;
        break;
    case PURPLE:
        r = 0.5;
        b = 1.0;
        break;
    case BLACK:
        r = g = b = 0.0;
        break;
    case GREY:
        r = g = b = 0.5;
        break;
    case WHITE:
        r = g = b = 1.0;
        break;
    default:
        break;
    }
    (*ptcr)->set_source_rgb(r, g, b);
}

void drawSquareFull(double x, double y, double cote, Color color){
    set_color(color);
    double xBL = x - cote/2;
    double yBL = y -cote/2;
    (*ptcr)->rectangle(xBL, yBL, cote, cote);
    (*ptcr)->fill(); 
}
void drawSquareEmpty(double x, double y, double cote, Color color){
    set_color(color);
    (*ptcr)->rectangle(x, y, cote, cote);
    (*ptcr)->stroke(); 
}

void drawCircleFull(double x, double y, double rayon, Color color){
    set_color(color);
    (*ptcr)->arc(x, y, rayon, 0.0, 2.0 * M_PI);
    (*ptcr)->fill();
}
void drawCircleEmpty(double x, double y, double rayon, Color color){
    set_color(color);
    (*ptcr)->arc(x, y, rayon, 0.0, 2.0 * M_PI);
    (*ptcr)->stroke();
}
