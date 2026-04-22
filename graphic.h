#ifndef GRAPHIC_H
#define GRAPHIC_H

enum Color
{
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    PURPLE,
    BLACK,
    GREY,
    WHITE,
};

void drawSquareFull(double x, double y, double cote, Color color);
void drawSquareEmpty(double x, double y, double cote, Color color);
void drawCircleFull(double x, double y, double rayon, Color color);
void drawCircleEmpty(double x, double y, double rayon, Color color);
#endif
