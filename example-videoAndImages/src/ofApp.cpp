#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{

    // pass the path to the media file you want to load. the size of the rectangle will be automatically set .
    image.setup("image.png");
    image.enableEdit();
    
    video.setup("fingers.mov");
    video.enableEdit();
    video.play();
    
}


//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 1));
}

//--------------------------------------------------------------
void ofApp::draw()
{
    
    image.draw();
    video.draw();
    
	stringstream ss;
	ss << "Click over the video or image and drag to reposition.\n";
	ss << "Drag the edges or corners of these to resize.\n\n";
	ss << "Press [key] for:\n";
	ss << "    [s]  : save current settings\n";
	ss << "    [l]  : load settings\n";
	ss << "    [1]  : enable rectangle editing\n";
	ss << "    [2]  : disable rectangle editing\n";
	ofBitmapFont bf;
	
	ofDrawBitmapStringHighlight(ss.str(), 30, ofGetHeight() - bf.getBoundingBox(ss.str(), 0, 0).height - 20);
	
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
	if(key == 's')
	{
		
		//(save with the default names. save in xml format. this is the same as calling it without arguments
		image.saveSettings("","", false);
		
		//save with a new name. This will also modify the name or the element. save in Json
		video.saveSettings("FingersVideo","",true);
		
		
	}
	else if(key == 'l')
	{
		
		// the arguments here are the same as when loading
		image.loadSettings();
		video.loadSettings("FingersVideo","",true);
	}
	else if(key == '1')
	{
		image.enableEdit();
		video.enableEdit();
	}
	else if(key == '2')
	{
		image.disableEdit();
		video.disableEdit();
	}

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
