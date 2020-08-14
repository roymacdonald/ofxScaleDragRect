#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	
	myRect.enableEdit();
	myRect.setRect(200, 200, 200, 400);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	
	// simply draw a yellow rectangle using our ofxInteractiveRect object.
	// As it inherits from ofRectangle you can simply pass it to ofDrawRectangle(...)
	ofSetColor(ofColor::red);
	ofDrawRectangle(myRect);
	
	// the following call will draw the rectangle's edge handles when editing.
	// call it after drawing the rectangle, otherwise the edge handles might not be visible
	myRect.draw();
	
	
	
	
	/// Draw some help messages
	stringstream ss;
	ss << "Click over the video or image and drag to reposition.\n";
	ss << "Drag the edges or corners of these to resize.\n\n";
	
	ss << "IS EDITING: " << boolalpha << myRect.isEditing() << "\n\n";
	
	ss << "Press [key] for:\n";
	
	ss << "    [s]      : save current settings\n";
	ss << "    [l]      : load settings\n";
	ss << "    [space]  : toggle editing\n";
	ss << "    [1]      : enable rectangle editing\n";
	ss << "    [2]      : disable rectangle editing\n";
	
	/// I use the ofBitmapFont to find the message hight so I can position it at the bottom of the screen, without need of guessing its height
	ofBitmapFont bf;
	
	ofDrawBitmapStringHighlight(ss.str(), 30, ofGetHeight() - bf.getBoundingBox(ss.str(), 0, 0).height - 20);
	
	
	
	
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	
	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == ' ')
	{
		myRect.toggleEdit();
	}
	else if(key == 's')
	{
		//(save with the default names. save in xml format. this is the same as calling it without arguments
		myRect.saveSettings("","", false);
		
		//save with a new name. This will also modify the name or the element. save in Json
//		myRect.saveSettings("FingersVideo","",true);
	}
	else if(key == 'l')
	{
		// the arguments here are the same as when loading
		myRect.loadSettings();
		
		//myRect.loadSettings("FingersVideo","",true);
	}
	else if(key == '1')
	{
		myRect.enableEdit();
	}
	else if(key == '2')
	{
		myRect.disableEdit();
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
