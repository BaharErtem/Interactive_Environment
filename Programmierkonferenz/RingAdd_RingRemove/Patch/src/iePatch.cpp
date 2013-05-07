#include "iePatch.h"

iePatch::iePatch(int defaultRings)
{
    int tempSize;
    if(ofGetWidth()>ofGetHeight())  // "Ist Fenster breiter als hoch?"
    {
        tempSize = ofGetHeight();  // "Ja!" - Temporaere Variable = Fensterhoehe
    }
    else
    {
        tempSize = ofGetWidth();  // "Nein!" - Temporaere Variable = Fensterbreite
    }

    marginX = tempSize/MARGIN_X;  // Margin = Fensterhoehe / -breite geteilt durch Faktor aus PraeProVariable, z.B. ein Zwanzigstel
    marginY = tempSize/MARGIN_Y;  // Jeweils fuer die X und Y Achse

    if(marginX>marginY)  // "Ist MarginX groe�er als MarginY?"
    {
        radius= .5*tempSize-marginY;  // Radius fuer Patch = Halbe Fensterhoehe minus Margin
    }
    else
    {
        radius= .5*tempSize-marginX;  // Radius fuer Patch = Halbe Fensterbreite minus Margin
    }

    centreX = .5*tempSize;  // Mittelpunkt fuer Patch = Halbe TempsizeX
    centreY = .5*tempSize;  // Mittelpunkt fuer Patch = Halbe TempsizeY


    for(int i=0; i<defaultRings; i++)
    {
        //rings.push_back(new ieRing(radius-((radius/nRings)*(i)),centreX,centreY,255-((255/nRings)*i)));  // F�llen des Vektorcontainers mit "nRings" neuen Ringen
        addRing();
    }
}

void iePatch::draw()
{
    ofSetColor(255,50,50);  // Farbe des "Hauptkreises"
    ofCircle(centreX,centreY,radius);  // "Hauptkreis", liegt im Hintergrund
    for(itRings=rings.begin(); itRings!=rings.end(); ++itRings)   // Iteration ueber alle im Vektor enthaltenen Ringe
    {
        (*itRings)->draw();  // Aufrufen der Draw-Methode f�r jeden einzelnen Ring
    }
    // rings[1]->draw();

}
void  iePatch::addRing()
{




    //rings.push_back(new ieRing(radius-(radius/nRings)*(nRings-1),centreX,centreY,255-((255/nRings)*(nRings-1))));
    rings.push_back(new ieRing(/*radius-(radius/nRings)*(nRings-1),*/centreX,centreY/*,255-((255/nRings)*(nRings-1))*/));
    reCalcRings();
}

void iePatch::removeRing()
{


    rings.pop_back();
    reCalcRings();



}
void iePatch::reCalcRings()
{

    int idx=0;

    for(itRings=rings.begin(); itRings!=rings.end(); ++itRings)
    {

        (*itRings)->setRadius(radius-(radius/rings.size())*(idx++));
        (*itRings)->setColor(255-(255/rings.size())*(idx*(255/rings.size())),100,100);
    }


}
