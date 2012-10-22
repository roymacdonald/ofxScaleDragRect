//
//  interactiveSequenceManager.h
//  JuegoDuckHunt
//
//  Created by Roy Macdonald on 8/18/12.
//  Copyright (c) 2012 micasa. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "interactiveSequence.h"
//#include "updateEvent.h"

class interactiveSequenceManager {
public:
    interactiveSequenceManager(){
        bIsEditing = false;
        bIsKeysEnabled = false;
    }
    ~interactiveSequenceManager(){}
    
    void draw();
    
    void mouseMoved(ofMouseEventArgs & mouse);
    void mousePressed(ofMouseEventArgs & mouse);
    void mouseDragged(ofMouseEventArgs & mouse);
    void mouseReleased(ofMouseEventArgs & mouse);
    
    void keyPressed(ofKeyEventArgs & key);
    void keyReleased(ofKeyEventArgs & key);
    
    void enableKeys(bool enable = true);
    void toggleKeys();
    
    void enableEdit(bool &enable);
    void toggleEdit();
    
    void enableDrawStatic(int num, bool enable = true);
    void enableDrawStaticAll(bool enable = true);
     
    vector<interactiveSequence>imgs;
    
    vector<ofRectangle> getPosElements(string cual);
    
    void loadFromDir(string dir);
    
    void drawAll();
    void playAll();
    
    bool getIsEditing(){return bIsEditing;}
    bool checkAt(int x, int y);
    vector<ofRectangle> pos; // este es para pasar los rects
    
protected:
        bool bIsKeysEnabled;
        bool bIsEditing;
        
 };
