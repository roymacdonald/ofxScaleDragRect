//
//  Perro.h
//  JuegoDuckHunt
//
//  Created by Roy Macdonald on 8/17/12.
//  Copyright (c) 2012 micasa. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "interactiveRect.h"
#include "ofxXmlSettings.h"

#define FRAMES_PER_FRAME 2

class interactiveSequence: public interactiveRect{
public:
    interactiveSequence(string nombre):interactiveRect::interactiveRect(nombre){
        bIsPlaying = false;
        bDrawStatic = false;
        bIsEnd = false;
        bDrawEdit = false;
        bSoundLoaded = false;
        frame = 0;
        frameCount = 0;
        this->nombre = nombre;
        path = "";
        bCheckAlpha = true;
        bDoLoop = false;
        frameDuration = FRAMES_PER_FRAME;
    }
    ~interactiveSequence(){}
    
    void setup(string path, string nombre, bool drawStatic = false){
        this->bDrawStatic = drawStatic;
        ofDirectory dir;
        dir.allowExt("png");
        dir.listDir(path);
        for (int i = 0; i < dir.numFiles(); i++) {
            img.push_back(ofImage());
            //if(!
            img.back().loadImage(dir[i].getAbsolutePath());//){
             //   cout << dir[i].getAbsolutePath()<<endl;
            //}
        }
        ofDirectory d;
        d.allowExt("wav");
        d.listDir(path);
        if (d.numFiles()>0){
        sound.loadSound(d.getPath(0));
        sound.setVolume(0.75f);
        sound.setMultiPlay(true);
            bSoundLoaded = true;
        }
        this->nombre = nombre;
        this->path = path;
        if(!loadSettings() && img.size()>0){
            this->ofRectangle::x = 0;
            this->ofRectangle::y = 0;
            this->ofRectangle::width = img[0].getWidth();
            this->ofRectangle::height = img[0].getHeight();
        }
      
 //       cout << "intractive Sequence Loaded: " << path << " " << nombre << endl;
    }
    void enableEdit(bool enable = true){
        interactiveRect::enableEdit(enable);
        this->bIsEditing = enable;
        if(!enable){
            saveSettings();
        }
    }
    void toggleEdit(){
        enableEdit(!this->bIsEditing);
    }
        
    void saveSettings(){
        interactiveRect::saveSettings();
        ofxXmlSettings settings;
        cout << "interactiveSequence save settings"<<endl;
        settings.loadFile(this->path + "settings" + this->nombre + ".xml");
       
        settings.addTag("interactiveSequence");
        settings.pushTag("interactiveSequence", settings.getNumTags("interactiveSequence")-1);
        settings.setValue("bDrawStatic", (string)(bDrawStatic?"true":"false"));
        settings.setValue("bCheckAlpha", (string)(bCheckAlpha?"true":"false"));
        settings.setValue("bDoLoop", (string)(bDoLoop?"true":"false"));
        settings.setValue("frameDuration", frameDuration);
        
        settings.popTag();
        settings.saveFile(this->path + "settings" + this->nombre + ".xml"); 
        settings.clear();
        cout << "saved settings XML: "<< this->path << "settings"<< this->nombre << ".xml" << endl;
    }

    
    bool loadSettings(){
        interactiveRect::loadSettings();
        ofxXmlSettings settings;
        if( settings.loadFile(this->path + "settings" + this->nombre + ".xml") ){
            cout << this->path << "settings" << this->nombre << ".xml loaded!" << endl;
            int tags = settings.getNumTags("interactiveSequence");
            if (tags>0) {
                settings.pushTag("interactiveSequence", tags-1);
                frameDuration = settings.getValue("frameDuration", FRAMES_PER_FRAME);
                bDrawStatic = ofToBool(settings.getValue("bDrawStatic", "false"));
                bCheckAlpha = ofToBool(settings.getValue("bCheckAlpha", "true"));
                bDoLoop = ofToBool(settings.getValue("bDoLoop", "false"));
                settings.popTag();
                settings.clear();
                return true;   
            }
            else{
                cout    << "invalid xml file!!!"<<endl;
                return false;
            }
        }else{
            cout << "unable to load " << this->path << "settings" << this->nombre << ".xml check data/ folder" << endl;
            return false;
        }        
    }
    void setDrawStatic(bool s = true){
        bDrawStatic = s;
    }
    void setFrame(int f){
        if  (frame < img.size() && frame >= 0){
            frame = f;
        }
    }
    int getTotalFrames(){
        return img.size();
    }
    void enableDrawEdit(bool drawEdit = true){
        bDrawEdit = drawEdit;
        frame = (int)(img.size()/2.0f);
        if (!drawEdit) {
            enableEdit(false);
        }
    }
    void play(int from =0){
        frame= from;
        bIsPlaying=true;
        bIsEnd=false;
        if(bSoundLoaded){
        sound.play();
        }
   //     cout << "interactiveSequence " << "play from " << frame << endl;
    }
    bool getIsPlaying(){return bIsPlaying;}

    bool getIsEnd(){return bIsEnd;}
    
    void draw(){
        this->interactiveRect::draw();
        if(bIsPlaying){
            frameCount++;
            if(frameCount > frameDuration){
                frame++;
                if (frame >= img.size()) {
                    bIsPlaying = bDoLoop;
                    bIsEnd =!bDoLoop;
                    frame = 0;
                }
                frameCount = 0;
            }
        }
        if(bIsPlaying || bDrawStatic || bDrawEdit){
        img[frame].draw(*this);
 //       cout << "draw "<< path << " frame "<< frame << endl;
    }
    }
    
    bool isOver(float x, float y){
        if (this->inside(x, y)) {
            if(bCheckAlpha){

                if(this->img[frame].getColor((x-getRectX())*(img[frame].getWidth()/ this->getRectWidth()), (y-getRectY()) *(img[frame].getHeight() / this->getRectHeight())  ).a > 0 ){
                return true;
            }else{
                return false;
            }
            }else{
                return true;
            }
        }else{
            return false;
        }
    }

    
private:
    int frame, frameCount;
    bool bDrawStatic;
    bool bDrawEdit;
    bool bIsPlaying;
    bool bIsEnd;
    int frameDuration;
    bool bCheckAlpha;
    bool bSoundLoaded;
    bool bDoLoop;
   // string path;
   ofSoundPlayer sound;

public:
    vector<ofImage> img;
};