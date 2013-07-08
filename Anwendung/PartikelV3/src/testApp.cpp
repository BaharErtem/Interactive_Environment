#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //Kinect initialisieren
    kinect.init();
    kinect.open();
    
    // Abfrage vom Kinect Winkel
    angle = kinect.getCurrentCameraTiltAngle(); 
    
    // Initialisierung des Graustufenbilds
    w = kinect.width;
    h = kinect.height;
    grayscaleImgInput.allocate(w, h);
    grayscaleImgFar.allocate(w, h);
    grayscaleImgNear.allocate(w, h);
    grayscaleImgOutput.allocate(w, h);
    
    //Schwellwert setzen
    thresholdFar = 255;             //maximale Tiefe der Kinect
    thresholdNear = 0;
    
    isThreshold = false;
    isBlur = false;
    isContour = false;
    isDebug = true;
    
    //Hintergrund schwarz setzen
    ofBackground(0, 0, 0);
    
    numParticles = 0;               //Anzahl Partikel
    maxNewParticles = 10;           //Anzahl Partikel die maximal erzeugt werden können
        
    screenH = ofGetScreenHeight();      //Breite & Höhe Screen
    screenW = ofGetScreenWidth();
    
    scale = (float) screenW / (float) w;            //Skalierung berechnen 
    cout << "screenW: " << screenW << " screenH: " << screenH << " scale: " << scale << endl;   //Ausgabe der Werte für Screen & Scale
    
    transX = 0;     //Variable für Verschiebung
    transY = 0;
    
    bigger = false;     //Modus für größere Schritte zu Beginn auf false
    step = 5;           //Schritte
    
}

//--------------------------------------------------------------
void testApp::update(){
    // Bild Aufnahme
    kinect.update();

    if (kinect.isFrameNew()){
        
        // Tiefenbild laden und speichern
        grayscaleImgInput.setFromPixels(kinect.getDepthPixels(), w, h);
        
        grayscaleImgFar = grayscaleImgInput;
        grayscaleImgNear = grayscaleImgInput;
        grayscaleImgOutput = grayscaleImgInput;
        
        //Abfrage ob isThreshold true
        if (isThreshold) {                                      
            grayscaleImgNear.threshold(thresholdNear);
            grayscaleImgFar.threshold(thresholdFar, true);
            cvAnd(grayscaleImgFar.getCvImage(), grayscaleImgNear.getCvImage(), grayscaleImgOutput.getCvImage(), NULL);
            grayscaleImgOutput.flagImageChanged();

        }
        
        //Weichzeichner anwenden
        if (isBlur) {
            grayscaleImgOutput.dilate_3x3();
            grayscaleImgOutput.dilate_3x3();
            grayscaleImgOutput.blur(5);
            grayscaleImgOutput.flagImageChanged();
        }
        
        //Kontur finden
        if (isContour) {    
            contourFinder.findContours(grayscaleImgOutput, 5, (w * h)/2, 3, false, true);
        }
    }
    
    if (!isDebug) {
            contourFinder.findContours(grayscaleImgOutput, 0, (w*h), 1, false, true);
        
        /*//Partikelsystem
        if (PartikelSystem.size() < MAXPARTICLES) {             //wenn PartikelSystem Größe kleiner als die maximale Partikelanzahl
                        
            numNewParticles = MAXPARTICLES - PartikelSystem.size();     //können neue Partikel erzeugt werden
            if (numNewParticles < maxNewParticles) {                    //wenn Anzahl der erzeugbaren Partikel kleiner als maximale Partikelanzahl
                stepSize = contourFinder.blobs[0].length / numNewParticles;             //dann Berechnung Schrittgröße mit numNewParticles
            }
            else
                stepSize = contourFinder.blobs[0].length / maxNewParticles;             //ansonsten mit maxNewParticles
                
            for (int i = 0; i < numNewParticles; i += stepSize) {
                PartikelSystem.push_back(new Partikel(contourFinder.blobs[0].pts.at(i).x, contourFinder.blobs[0].pts.at(i).y));                                    //Erzeugung eines Partikels an x & y der Kontur
            }
        }*/
    }
    /*if (PartikelSystem.size() > 0) {
        for (int j = 0; j < PartikelSystem.size(); j++) {
            PartikelSystem.at(j)->update();                      //update für Ermittlung neuer Position der Partikel
        }
    }*/
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if(isDebug) {
        
        ofSetColor(255, 255, 255);
        grayscaleImgInput.draw(0, 0, 320, 240);
        grayscaleImgFar.draw(321, 0, 320, 240);
        grayscaleImgNear.draw(0, 241, 320, 240);
        grayscaleImgOutput.draw(321, 241, 320, 240);
        contourFinder.draw(321, 241, 320, 240);
        
        
        ofSetColor(255, 0, 255);
        ofDrawBitmapString("Standard Bild", 10, 10);
        ofDrawBitmapString("ThresholdFar", 331, 10);
        ofDrawBitmapString("ThresholdNear", 10, 251);
        ofDrawBitmapString("Output", 331, 251);
        
        ofDrawBitmapString("Winkel der Kinect: " + ofToString(angle), 10, 20);
        ofDrawBitmapString("f = fullscreen, Pfeiltasten = verschieben", 10, 500);
        ofDrawBitmapString("+/- = groeßer/kleiner, a = +/- Schritt hoeher", 10, 510);

    }
    /*else
    {
        if (PartikelSystem.size()){
            for (int i = 0; i < PartikelSystem.size(); i++) {
                ofSphere(PartikelSystem.at(i)->pos.x, PartikelSystem.at(i)->pos.y, 5);      //Partikel anzeigen
            }
        }*/
        
        //Pixelwolke statt Partikelsystem
        for(int i = 0; i < contourFinder.nBlobs; i++) {
            
            ofBeginShape();
            for (int j = 0; j < contourFinder.blobs.at(i).nPts; j++){
                
                ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
                //ofSphere((contourFinder.blobs.at(i).pts[j].x * scale) + transX, (contourFinder.blobs.at(i).pts[j].y * scale) - transY, 5);
                ofSphere((contourFinder.blobs.at(i).pts[j].x + ofRandom(0, 20) * scale) + transX, (contourFinder.blobs.at(i).pts[j].y + ofRandom(0, 20) * scale) - transY, 3);
                //Pixel zeichnen und anzeigen

            }
            ofEndShape(true);
            
        }
      
    }


//--------------------------------------------------------------

void testApp::exit() {
	kinect.close();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch (key) {
        // Winkel der Kinect nach oben ändern
        case 'w':
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
        
        // Winkel der Kinect nach unten ändern
		case 's':
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
            
        //Threshold aktivieren
        case 't':                           
            isThreshold = !isThreshold;
            break;
            
        //Weichzeichner aktivieren
        case 'b':                          
            isBlur = !isBlur;
            break;
    
        //Blobs ermitteln
        case 'c':                           
            isContour = !isContour;
            break;
        
        //zu Anzeigefenster wechseln 
        case ' ':
            isDebug = !isDebug;
            break;
          
        //Vollbildmodus aktivieren
        case 'f':
            ofToggleFullscreen();
            screenW = ofGetScreenWidth();
            screenH = ofGetScreenHeight();
            cout << screenW ;
            break;
        
        //Vergrößern
        case '+':
            scale += 0.01;
            break;
         
        //Verkleinern
        case '-':
            scale -= 0.01;
            break;
        
        //Verschieben nach links
        case OF_KEY_LEFT:
            transX -= step;
            break;
           
        //Verschieben nach rechts
        case OF_KEY_RIGHT:
            transX += step;
            break;
        
        //Verschieben nach oben
        case OF_KEY_UP:
            transY += step;
            break;
        
        //Verschieben nach unten
        case OF_KEY_DOWN:
            transY -= step;
            break;
        
        //Verschieben mit größeren Schritten aktiviert
        case 'a':
            bigger = !bigger;
            if (bigger) {
                step = 20;
            } else
                step = 5;
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}