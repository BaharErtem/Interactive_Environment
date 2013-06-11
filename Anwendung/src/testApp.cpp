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
    thresholdFar = 2000;
    thresholdNear = 100;
    
    isThreshold = false;
    isBlur = false;
    isContour = false;
    isDebug = true;
    
    //Hintergrund schwarz setzen
    ofBackground(0, 0, 0);
    
    numParticles = 0;
    
    bHide = false;
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
        
        //Weichzeichner
        if (isBlur) {
            grayscaleImgOutput.dilate_3x3();
            grayscaleImgOutput.dilate_3x3();
            grayscaleImgOutput.blur(5);
            grayscaleImgOutput.flagImageChanged();
        }
        
        if (isContour) {
            contourFinder.findContours(grayscaleImgOutput, 5, (w * h)/2, 3, false, true);
        }
    }
    
    if (!isDebug) {

            contourFinder.findContours(grayscaleImgOutput, 0, (w * h), 1, false, true);
        
        if (PartikelSystem.size() < 5000) {
            //ofPixels pixels = kinect.getPixelsRef();
            
            PartikelSystem.push_back(new Partikel(ofRandom(0, w), ofRandom(0, h)));

            //PartikelSystem.push_back(new Partikel(w+ofRandom(0, 5), h+ofRandom(0, 5)));
           
            //PartikelSystem.push_back(new Partikel(pixels.getWidth(), pixels.getHeight()));           //Erzeugung eines neuen Partikels
            
            //PartikelSystem.push_back(new Partikel(w/2, h/2));           //Erzeugung eines neuen Partikels
            
//            PartikelSystem.push_back(new Partikel(w/2+200, h/2+2));           //Erzeugung eines neuen Partikels
//            PartikelSystem.push_back(new Partikel(w/2+40, h/2+4));           //Erzeugung eines neuen Partikels
        }
        else if (bHide)
        {
            PartikelSystem.clear();
            bHide = false;
        }
        else if (PartikelSystem.size() == 5000)
        {
            bHide = true;
        }
    }
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
    }
    else
    {
        /*if (bHide)
            ofSetColor(0, 0, 0);
        else
            ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));*/
        //ofSetColor(255,255,255);
        //int i = 0;
        //ofBeginShape();
        for (itP = PartikelSystem.begin(); itP != PartikelSystem.end(); itP++) {
            //ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
            if (bHide)
                ofSetColor(0, 0, 0);
            else
                ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
            
            ofSphere((*itP)->pos.x, (*itP)->pos.y, 0, 2);
            //ofVertex((*itP)->pos.x, (*itP)->pos.y);
            //gl_Vertex((*itP)->pos.x, (*itP)->pos.y);  //zur not mit array wenn keine L�sung
            /*ofDrawBitmapString("Position Vertex: x= " + ofToString((*itP)->pos.x) + " y= " + ofToString((*itP)->pos.y), 10, 10 + (i*10));
            i++;*/
        }
        //ofEndShape(true);
        
        
        //contourFinder.draw();
        for(int i = 0; i < contourFinder.nBlobs; i++) {
            
            //contourFinder.blobs.at(i).draw();
            //ofNoFill();
            ofBeginShape();
            for (int j = 0; j < contourFinder.blobs.at(i).nPts; j++){
                ofSetColor(0, 0, 0);
                
                ofVertex(0 + contourFinder.blobs.at(i).pts[j].x, 0 + contourFinder.blobs.at(i).pts[j].y);
                /*ofDrawBitmapString("Position Vertex: x= " + ofToString(contourFinder.blobs.at(i).pts[j].x) + " y= " + ofToString(contourFinder.blobs.at(i).pts[j].y), 10, 10 + (i*10));*/
            }
            ofEndShape(true);
            
        }
        
        
        /*grayscaleImgOutput.draw(0, 240, 320, 240);
        ofRect(320, 0, 320, 240);
        contourFinder.draw();
        ofColor c(255, 255, 255);
        for(int i = 0; i < contourFinder.nBlobs; i++) {
            ofRectangle r = contourFinder.blobs.at(i).boundingRect;
            r.x += 320; r.y += 240;
            c.setHsb(i * 64, 255, 255);
            ofSetColor(c);
            ofRect(r);
        }*/
        
        //ofSetPolyMode(OF_POLY_WINDING_ODD);
        //ofBeginShape();
//        ofSetColor(0,0,255);
//        for (int i = 0; i < PartikelSystem.size(); i++) {
//            ofVertex(PartikelSystem[i]->pos.x, PartikelSystem[i]->pos.y);
//        }
        //ofEndShape();
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
    // Winkel der Kinect �ndern
    switch (key) {
        case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
			
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
            
        case 't':                           //Schwellwert abschalten mit "t"
            isThreshold = !isThreshold;
            break;
            
        case 'b':                           //Weichzeichner
            isBlur = !isBlur;
            break;
    
        case 'c':                           //Blobs
            isContour = !isContour;
            break;
            
        case ' ':
            isDebug = !isDebug;
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