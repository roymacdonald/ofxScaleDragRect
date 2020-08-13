//
//  interactiveSequenceManager.cpp
//  JuegoDuckHunt
//
//  Created by Roy Macdonald on 8/15/12.
//  Copyright (c) 2012 micasa. All rights reserved.
//

#include "interactiveSequenceManager.h"

//--------------------------------------------------------------
void interactiveSequenceManager::draw(){
    for (int i = 0; i <imgs.size(); i++) {
        imgs[i].draw();
    }   
}
//--------------------------------------------------------------
void interactiveSequenceManager::enableDrawStaticAll(bool enable){
    for (int i = 0; i < imgs.size(); i++) {
        imgs[i].setDrawStatic(enable);    
    }
}
//--------------------------------------------------------------
void interactiveSequenceManager::enableDrawStatic(int num, bool enable){
    if (num < imgs.size()) {
        imgs[num].setDrawStatic(enable);
    }
}
//--------------------------------------------------------------
void interactiveSequenceManager::enableEdit(bool &enable){
    if (enable) {
        ofRegisterMouseEvents(this);
    }else{
        ofUnregisterMouseEvents(this);
    }
    for (int i = 0; i<imgs.size(); i++) {
        imgs[i].enableDrawEdit(enable);
    }
    bIsEditing= enable;  
}
//--------------------------------------------------------------
void interactiveSequenceManager::toggleEdit(){
    bool e = !bIsEditing;
    enableEdit(e);   
}

//--------------------------------------------------------------
void interactiveSequenceManager::drawAll(){
    for (int i = 0; i < imgs.size(); i++) {
        imgs[i].play();
    }
}
//--------------------------------------------------------------
void interactiveSequenceManager::playAll(){
    for (int i = 0; i < imgs.size(); i++) {
        imgs[i].draw();
    }
}
//--------------------------------------------------------------
void interactiveSequenceManager::loadFromDir(string dir){
    cout << "loading from dir "<< dir << endl;
    ofDirectory d;
    int cuantos = d.listDir(dir);
    for (int i = 0; i < cuantos; i++) {
        if (d.getFile(i).isDirectory()) {
            imgs.push_back(interactiveSequence(d.getName(i)));
            imgs.back().setup(dir+d.getName(i)+"/", d.getName(i));
        }
    }
}
//--------------------------------------------------------------
vector<ofRectangle> interactiveSequenceManager::getPosElements(string cual){
        for (int i = 0; i < imgs.size(); i++) {
            size_t found;
            found=ofFilePath::getFileName(imgs[i].nombre).find(cual);
            if (found!=string::npos){
                pos.push_back(imgs[i].getRect());
                cout << "found " << imgs[i].nombre << " " << pos.back().x << " " <<  pos.back().y << " " << pos.back().width << " " << pos.back().height << endl;
            }
        }
    return pos;
}
//--------------------------------------------------------------
void interactiveSequenceManager::mouseMoved(ofMouseEventArgs & mouse){
}
//--------------------------------------------------------------
void interactiveSequenceManager::mousePressed(ofMouseEventArgs & mouse){
    cout << "mouse button " << mouse.button << endl;
    for (int i = 0; i<imgs.size(); i++) {
        if (imgs[i].isOver(mouse.x, mouse.y)){    
            imgs[i].enableEdit();
        }else{
            if(!imgs[i].inside(mouse.x, mouse.y)){
                imgs[i].enableEdit(false);
            }
        }
    }
}
//--------------------------------------------------------------
void interactiveSequenceManager::mouseDragged(ofMouseEventArgs & mouse){
}
//--------------------------------------------------------------
void interactiveSequenceManager::mouseReleased(ofMouseEventArgs & mouse){
}

//--------------------------------------------------------------
void interactiveSequenceManager::mouseScrolled(ofMouseEventArgs & mouse) {}
void interactiveSequenceManager::mouseEntered(ofMouseEventArgs & mouse) {}
void interactiveSequenceManager::mouseExited(ofMouseEventArgs & mouse) {}

//--------------------------------------------------------------
void interactiveSequenceManager::enableKeys(bool enable){
    if (enable != bIsKeysEnabled) {
        if (enable) {
            ofRegisterKeyEvents(this);
        }else{
            ofUnregisterKeyEvents(this);
        }
        bIsKeysEnabled = enable;
    }
}
//--------------------------------------------------------------
void interactiveSequenceManager::toggleKeys(){
    enableKeys(!bIsKeysEnabled);
}
//--------------------------------------------------------------
void interactiveSequenceManager::keyPressed(ofKeyEventArgs & key){
    if (key.key >= '0' && key.key <= '9') {
        int k = key.key - '0';
        if (k<imgs.size()) {
            imgs[k].play();
        }
    }
}
//--------------------------------------------------------------
void interactiveSequenceManager::keyReleased(ofKeyEventArgs & key){
    
}

//--------------------------------------------------------------
bool interactiveSequenceManager::checkAt(int x, int y){
    bool over = false;
    if(!bIsEditing){
    for (int i = 0; i < imgs.size(); i++) {
        if (imgs[i].isOver(x, y)) {
            imgs[i].play();
            over = true;
        }
    }
    }
    return over;
}
