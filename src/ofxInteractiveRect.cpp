//
//  interactiveRect.cpp
//
//  Created by Roy Macdonald on 8/15/12.
//  Copyright (c) 2012 micasa. All rights reserved.
//
//  Updated by Aaron Richards on 13/05/2014.
//

#include "ofxInteractiveRect.h"



//--------------------------------------------------------------
ofxInteractiveRect::ofxInteractiveRect(string nombre)
{
    bIsEditing = false;
    bMove = false;
    bLeft = false;
    bRight = false;
    bUp = false;
    bDown = false;
	bIsOver = false;
    this->nombre = nombre;
    this->path = "";
}
//--------------------------------------------------------------
ofxInteractiveRect::~ofxInteractiveRect()
{
}

//--------------------------------------------------------------
void ofxInteractiveRect::enableEdit(bool enable)
{
    
    cout << "interactiveRect " << this->nombre <<" enableEdit " << (string)(enable?"true":"false") << endl; 
    
    if (enable != bIsEditing)
    {
        if (enable)
        {
            ofRegisterMouseEvents(this);
        }
        else
        {
            ofUnregisterMouseEvents(this);
          //  saveSettings();
        }
        bIsEditing = enable;
        
    }
    
}

//--------------------------------------------------------------
void ofxInteractiveRect::disableEdit()
{
    enableEdit(false);
}	

//--------------------------------------------------------------
void ofxInteractiveRect::toggleEdit()
{
    enableEdit(!bIsEditing);
}

//--------------------------------------------------------------
ofRectangle ofxInteractiveRect::getRect()
{
    return ofRectangle(x, y, width, height);
}

//--------------------------------------------------------------
void ofxInteractiveRect::saveSettings(string nombre, string path)
{
    
    if(nombre!="")
    {
        this->nombre = nombre;
    }
    
    if (path!="")
    {
        this->path = path;
    }
    
    ofxXmlSettings settings;
  //  settings.clear();
    settings.addTag("interactiveRect");
    settings.pushTag("interactiveRect", settings.getNumTags("interactiveRect")-1);
//    settings.setValue("tipo", t);
    settings.setValue("path", this->path);
    settings.setValue("x",this->ofRectangle::x);
    settings.setValue("y",this->ofRectangle::y);
    settings.setValue("width", this->ofRectangle::width);
    settings.setValue("height", this->ofRectangle::height);
    settings.setValue("nombre", this->nombre);
    settings.popTag();
    settings.saveFile(this->path + "settings" + this->nombre + ".xml"); 
    settings.clear();
    cout << "saved settings XML: "<< this->path << "settings"<< this->nombre << ".xml" << endl;
    
}
//--------------------------------------------------------------
bool ofxInteractiveRect::loadSettings(string nombre, string path)
{
    
    ofxXmlSettings settings;
    if (nombre != "" )
    {
        this->nombre = nombre;
    }
    
    if (path!="")
    {
        this->path = path;
    }
	
    if( settings.loadFile(this->path + "settings" + this->nombre + ".xml") )
    {
        
		cout << this->path << "settings" << this->nombre << ".xml loaded!" << endl;
        
        int tags = settings.getNumTags("interactiveRect");
        if (tags>0)
        {
            settings.pushTag("interactiveRect", tags-1);
            this->ofRectangle::x = settings.getValue("x", 0);
            this->ofRectangle::y = settings.getValue("y", 0);
            this->ofRectangle::width = settings.getValue("width", 0);
            this->ofRectangle:: height = settings.getValue("height", 0); 
            this->nombre = settings.getValue("nombre", this->nombre);
            settings.popTag();
            settings.clear();
            return true;   
        }
        else
        {
            cout    << "invalid xml file!!!"<<endl;
            return false;
        }
        
    }
    else
    {
        cout << "unable to load " << this->path << "settings" << this->nombre << ".xml check data/ folder" << endl;
        return false;
    }
    
}
    

//--------------------------------------------------------------
void ofxInteractiveRect::draw()
{
    
	if (bIsEditing)
    {
    
        ofPushStyle();
		if (bIsOver)
        {
			if (bPressed)
            {
				ofSetColor(50, 200);				
			}
            else
            {
				ofSetColor(50, 70);				
			}
			ofNoFill();
			ofRect(*this);
			
		}
        
		ofFill();
        if (bMove)
        {
            ofSetColor(127, 127);
            ofRect(*this);
        }
        else
        {
            ofSetColor(255, 255, 0, 150);
            
            if (bUp)
            {
                ofRect(x, y, width, MARGEN);
            }
            else if(bDown)
            {
                ofRect(x, y + height - MARGEN, width, MARGEN);
            }
            
            if (bLeft)
            {
                ofRect(x, y, MARGEN, height);
            }
            else if(bRight)
            {
                ofRect(x + width - MARGEN, y, MARGEN, height);
            }
        }
        ofPopStyle();
        
	}
    
}

//--------------------------------------------------------------
void ofxInteractiveRect::mouseMoved(ofMouseEventArgs & mouse)
{
    
	if (!bPressed)
    {
		
		bIsOver = inside(mouse.x, mouse.y);

		bLeft = false;
		bRight = false;
		bUp = false;
		bDown = false;
	
        if (bIsOver)
        {
			bMove = true;
		
            if (mouse.x < x+MARGEN && mouse.x > x)
            {
				bLeft = true;
				bMove = false;
			}
            else if(mouse.x < x + width && mouse.x > x + width - MARGEN)
            {
				bRight = true;
				bMove = false;
			}
			
            if (mouse.y > y && mouse.y < y + MARGEN)
            {
				bUp = true;
				bMove = false;
			}
            else if(mouse.y > y + height - MARGEN && mouse.y < y + height)
            {
				bDown = true;
				bMove = false;
			}
		}
        else
        {
			bMove = false;
		}

	}
    
}
//--------------------------------------------------------------
void ofxInteractiveRect::mousePressed(ofMouseEventArgs & mouse)
{
    
    mousePrev.set(mouse.x, mouse.y);
	bPressed = true;
    bIsOver = inside(mouse.x, mouse.y);
    
    bLeft = false;
    bRight = false;
    bUp = false;
    bDown = false;
    
    if (bIsOver)
    {
        bMove = true;
        if (mouse.x < x+MARGEN && mouse.x > x)
        {
            bLeft = true;
            bMove = false;
        }
        else if(mouse.x < x + width && mouse.x > x + width - MARGEN)
        {
            bRight = true;
            bMove = false;
        }
        if (mouse.y > y && mouse.y < y + MARGEN)
        {
            bUp = true;
            bMove = false;
        }
        else if(mouse.y > y + height - MARGEN && mouse.y < y + height)
        {
            bDown = true;
            bMove = false;
        }
    }
    else
    {
        bMove = false;
    }

}
//--------------------------------------------------------------
void ofxInteractiveRect::mouseDragged(ofMouseEventArgs & mouse)
{
    
    if (bUp)
    {
        y += mouse.y - mousePrev.y;
        height += mousePrev.y- mouse.y;
    }
    else if (bDown)
    {
        height += mouse.y - mousePrev.y;
    }
    if (bLeft)
    {
        x += mouse.x - mousePrev.x;
        width += mousePrev.x - mouse.x;
    }
    else if (bRight)
    {
        width += mouse.x - mousePrev.x;
    }
    if (bMove)
    {
        x += mouse.x - mousePrev.x;
        y += mouse.y - mousePrev.y;
    }
    
    mousePrev.set(mouse.x, mouse.y);
    
}
//--------------------------------------------------------------
void ofxInteractiveRect::mouseReleased(ofMouseEventArgs & mouse)
{
    
    bMove = false;
    bLeft = false;
    bRight = false;
    bUp = false;
    bDown = false;
	bPressed = false;
    
}