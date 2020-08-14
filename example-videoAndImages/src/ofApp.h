#pragma once

#include "ofMain.h"

#include "ofxInteractiveImage.h"
#include "ofxInteractiveVideo.h"

class ofApp : public ofBaseApp
{

	public:
    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
	
		// the string with which you initialize these is the name of each, and it will be saved with such name when you dont provide one in the saveSettings function
		ofxInteractiveImage image = {"Image"};
		ofxInteractiveVideo video = {"Video"};
		
};
