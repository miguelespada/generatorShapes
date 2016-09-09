//
//  Triangle.h
//  generator
//
//  Created by miguel on 01/09/16.
//
//

#ifndef generator_Triangle_h
#define generator_Triangle_h

#include "ofMain.h"

class Shape{
    
public:
    ofPoint center;
    int rotation;
    int color;
    int scale;
    int shape;
    vector<ofImage *> shapes;
    vector<int> colors;
    ofPoint anchor;
    
    Shape(){
        color = 0;
        rotation = 0;
        scale = 5;
        shape = 0;
        center.x = 0;
        center.y = 0;
        anchor = ofPoint(300, 300);
    }
    
    
    
    string toString(){
        return
        ofToString(shape) + ";" + ofToString(rotation) + ";" +
        ofToString(scale) + ";" + ofToString(color) + ";" +
        ofToString(center.x) + ";" + ofToString(center.y);
    }
    
    void fromSring(string line){
        vector<string> tokens = ofSplitString(line, ";");
        int j = ofToInt(tokens[0]);
        shape =  ofToInt(tokens[1]);
        rotation =  ofToInt(tokens[2]);
        scale =  ofToInt(tokens[3]);
        color =  ofToInt(tokens[4]);
        center.x =  ofToInt(tokens[5]);
        center.y =  ofToInt(tokens[6]);
    }
    
    void draw(){
        shapes[shape]->setAnchorPercent(0.5, 0.5);
        ofPushMatrix();
        ofSetHexColor(colors[color]);
        ofTranslate(center);
        ofRotate(rotation);
        ofScale(scale / 10.0, scale / 10.0);
        
        shapes[shape]->draw(0, 0);
        ofPopMatrix();
    
    }
    
    
    
    
    
};
#endif
