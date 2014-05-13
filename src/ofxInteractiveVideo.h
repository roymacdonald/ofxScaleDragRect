//
//  ofxInteractiveVideo.h
//
//  Created by Aaron Richards on 13/05/2014.
//
//

#ifndef scaleDrag_ofxInteractiveVideo_h
#define scaleDrag_ofxInteractiveVideo_h

#include "ofMain.h"
#include "ofxInteractiveRect.h"

class ofxInteractiveVideo : public ofxInteractiveRect, public ofVideoPlayer
{
    
public:
    
    ofxInteractiveVideo(string nombre):ofxInteractiveRect::ofxInteractiveRect(nombre)
    {
        path = "";
	}
    
    ~ofxInteractiveVideo()
    {
        ofRemoveListener(ofEvents().update, this, &ofxInteractiveVideo::updateVideo);
    }
    
    
    void setup(string path)
    {
        
        this->path = path;
        if(this->loadMovie(path))
        {
            
            this->ofxInteractiveRect::set(x,y,this->ofVideoPlayer::getWidth(),this->ofVideoPlayer::getHeight());
            cout << "loaded " << path << endl;
            ofAddListener(ofEvents().update, this, &ofxInteractiveVideo::updateVideo);
        }
        else
        {
            cout << "couldn load " << path << endl;
        }
        
    }
    
    void setup(string path, float x, float y, float w, float h)
    {
        
        this->path = path;
        if(this->loadMovie(path))
        {
            this->ofxInteractiveRect::set(x,y,w,h);
            cout << "loaded " << path << " " << x << " " << y << " " << w << " " << h << endl;
        }
        else
        {
            cout << "couldn load " << path << endl;
        }
        
    }
    
    void updateVideo(ofEventArgs &e)
    {
        this->update();
    }
    
    void draw()
    {
        draw(x, y);
    }
    
    void draw(float x, float y)
    {
        
        this->x = x;
        this->y = y;
        this->ofVideoPlayer::draw(this->x, this->y, this->ofxInteractiveRect::width, this->ofxInteractiveRect::height);
        ofxInteractiveRect::draw();
        
    }
    
    void drawImgAtY(float y)
    {
        this->ofVideoPlayer::draw(this->x, y, this->ofxInteractiveRect::width, this->ofxInteractiveRect::height );
    }
    
    void drawImgAtX(float x)
    {
        this->ofVideoPlayer::draw(x, this->y, this->ofxInteractiveRect::width, this->ofxInteractiveRect::height );
    }
    
//    bool isOver(float x, float y)
//    {
//        
//        if (this->inside(x, y))
//        {
//            cout << this->ofVideoPlayer::getColor(x, y) << endl;
//            if(this->ofVideoPlayer::getColor(x, y).a > 0 )
//            {
//                return true;
//            }
//            else
//            {
//                return false;
//            }
//        }
//        else
//        {
//            return false;
//        }
//        
//    }
    
};

#endif
