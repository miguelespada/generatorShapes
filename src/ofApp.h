#pragma once

#include "ofMain.h"
#include "shape.h"
#define N 36

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void loadShapes(string path);
    
    string ToFilename();
    
    void readFile();
    void saveFile();
    
    vector<Shape *> steps[N];
    
    int c = 0;
    
    int prev;
    bool bPressed;
    bool bPlay;
    bool playSide;
    bool bEdited;
    
    ofFile file;
    ofBuffer buffer;
    
    vector<int> colors;
    vector<ofImage *> shapes;

    
    int folder = 0;
    
    Shape *s;
};
