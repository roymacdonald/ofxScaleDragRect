//
//  interactiveImage.h
//  JuegoDuckHunt
//
//  Created by Roy Macdonald on 8/15/12.
//  Copyright (c) 2012 micasa. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "interactiveRect.h"

class interactiveImage : public interactiveRect, public ofImage{

public:
    interactiveImage(string nombre):interactiveRect::interactiveRect(nombre){
        path = "";
	}
    ~interactiveImage(){}
    
    void setup(string path, float x, float y, float w, float h){
        this->path = path;
        if(this->loadImage(path)){
        this->interactiveRect::set(x,y,w,h);
                cout << "loaded " << path << " " << x << " " << y << " " << w << " " << h << endl;
        }else{
            cout << "couldn load " << path << endl;
        }
    }
    void load(string path){
        this->path = path;
        if(this->loadImage(path)){
            this->ofRectangle::set(0, 0, this->ofImage::getWidth(), this->ofImage::getHeight());
            cout << "loaded " << path << endl;
        }else{
            cout << "couldn load " << path << endl;
        }
    }
    void draw(){
        draw(x, y);
    }
    void draw(float x, float y){
        this->x = x;
        this->y = y;
        this->ofImage::draw(this->x, this->y, this->interactiveRect::width, this->interactiveRect::height);
        interactiveRect::draw();
    }
    void drawImgAtY(float y){
        this->ofImage::draw(this->x, y, this->interactiveRect::width, this->interactiveRect::height );
    
    }
    void drawImgAtX(float x){
        this->ofImage::draw(x, this->y, this->interactiveRect::width, this->interactiveRect::height );
        
    }
    
    bool isOver(float x, float y){
        if (this->inside(x, y)) {
            cout << this->ofImage::getColor(x, y) << endl;
            if(this->ofImage::getColor(x, y).a > 0 ){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
//    string path;
};
