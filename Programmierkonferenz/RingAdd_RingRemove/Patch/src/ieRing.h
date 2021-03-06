#ifndef IERING_H_INCLUDED
#define IERING_H_INCLUDED
#include "ofMain.h"
#define PADDING 5

class ieRing
{
public:
    ieRing(/*int radiusOut,*/ int centreX, int centreY/*, int color*/);
    void draw();
    void setRadius(int radius);
    void setColor(int r,int g,int b);

private:
    int radiusIn;
    int radiusOut;
    int centreX, centreY;
    ofColor color;
};


#endif // IERING_H_INCLUDED
