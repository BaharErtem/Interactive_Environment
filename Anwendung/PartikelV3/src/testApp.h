#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "Partikel.h"
#define MAXPARTICLES 1000

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        
        int w; // Breite des Kinect Bildes
        int h; // Höhe des Kinect Bildes
            
        void exit();
    
private:
    ofxKinect kinect;
    ofxCvGrayscaleImage grayscaleImgInput;
    ofxCvGrayscaleImage grayscaleImgFar;
    ofxCvGrayscaleImage grayscaleImgNear;
    ofxCvGrayscaleImage grayscaleImgOutput;
    ofxCvContourFinder contourFinder;

    
    int thresholdFar, thresholdNear; //Schwellwerte
    
    int angle;                  //Winkel Kinect
    bool isThreshold;           //Schwellwert
    bool isBlur;                //Weichzeichner
    bool isContour;             //Silhoutte 
    bool isDebug;               //Umschalten in Debug Modus
    
    vector<Partikel*> PartikelSystem;           //PartikelSystem ist Vektor mit Pointer auf Partikel
    
    int numParticles;                           //Anzahl Partikel
    std::vector<Partikel*>::iterator itP;
    
    int screenH, screenW;           //Variablen um Screen vergrößern/verkleinern zu können
    
    float scale;                    //Variable zur Skalierung
    int transX, transY;             //Variablen für Verschiebung
    bool bigger;                    //Nötig um Verschiebungsschritte vergrößern zu können bei Bedarf
    int step;                       //Verschiebungsschritte
        
    int maxNewParticles;            //Anzahl Partikel die maximal erzeugt werden können
    int numNewParticles;            //Anzahl Partikel die wir erzeugen möchten
    int stepSize;                   //Abtastschritt an Kontur
		
};
