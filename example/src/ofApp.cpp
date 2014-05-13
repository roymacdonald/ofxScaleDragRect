#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{

    image = new ofxInteractiveImage("Image");
    image->setup("image.png");
    image->enableEdit();
    
    video = new ofxInteractiveVideo("Video");
    video->setup("fingers.mov");
    video->enableEdit();
    video->play();
    
}

//--------------------------------------------------------------
void ofApp::exit()
{
    
    delete image;
    delete video;
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 1));
}

//--------------------------------------------------------------
void ofApp::draw()
{
    
    image->draw();
    video->draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
