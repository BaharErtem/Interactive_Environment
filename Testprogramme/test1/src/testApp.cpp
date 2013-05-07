#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    nBalls = 10;    // Anzahl der Baelle

    myBall = new ofBall*[nBalls];

    for(int i=0;i<nBalls;i++)
    {
        float x = 20+(100*i);
        float y = 20+(100*i);
        int dim = 10+(10*i);

        myBall[i]= new ofBall(x,y,dim);
    }
}

//--------------------------------------------------------------
void testApp::update(){

   for(int i=0;i<nBalls;i++)
   {
       myBall[i]->update();
   }
}

//--------------------------------------------------------------
void testApp::draw(){

    for(int i=0;i<nBalls;i++)
    {
        myBall[i]->draw();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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
