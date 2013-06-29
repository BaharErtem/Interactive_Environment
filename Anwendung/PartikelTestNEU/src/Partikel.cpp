#include "Partikel.h"

Partikel::Partikel(int x, int y)
{
    vel.x = ofRandom(-1, 1);        //Geschwindigkeit
    vel.y = 0.5;
    pos.x = x;                      //Position
    pos.y = y;
}

void Partikel::update (){
    pos.x += vel.x;             //neue Position Partikel
    pos.y += vel.y;
}