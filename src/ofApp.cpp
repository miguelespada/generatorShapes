#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableAntiAliasing();
    
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(0, 255, 255);
    
    bPressed = false;
    bPlay = false;
    bEdited = false;
    
    
    colors.push_back(0x000);
    colors.push_back(0xffffff);
    colors.push_back(0xaaaaaa);
    colors.push_back(0xff1222);
    colors.push_back(0x0048d4);
    colors.push_back(0xfcfc00);
    colors.push_back(0xff1eaa);
    colors.push_back(0xff41ff);
    colors.push_back(0x00d8fd);
    colors.push_back(0xff4c1f);
    
    
    loadShapes("shapes");
    
    s = new Shape();
    s->colors = colors;
    s->shapes = shapes;
    
    ofEnableAlphaBlending();
    
    readFile();
    
}


void ofApp::loadShapes(string path){
    ofDirectory dir(path);
    
    
    dir.open(path);
    
    dir.allowExt("png");
    dir.listDir();
    
    dir.sort();
    
    for(int i = 0; i < dir.size(); i++){
        cout << "[LOADING] " << dir.getPath(i) << endl;
        ofImage *img = new ofImage();
        img->load(dir.getPath(i));
        shapes.push_back(img);
    }
    return dir.size();
    
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 255, 255);
    
    
    
    for(int i = 0; i < steps[c].size(); i++){
        steps[c][i]->draw();
    }
    
    s->center.x = mouseX;
    s->center.y = mouseY;
    
    s->draw();
    if(bPressed) {
        ofSetHexColor(colors[s->color]);
        
    }
    
    
    if(bPlay){
        string filename = ToFilename() + "/" + ofToString(c, 2, '0') + ".png";
        ofSaveScreen(filename);
        c += 1;
        if(c == N && folder == 1){
            bPlay = false;
            c = 0;
            folder = 0;
            cout << "DONE!" << endl;
        }
        else{
            if(c == N){
                c = 0;
                folder += 1;
                readFile();
            }
        }
            
        
        cout << filename << endl;

    }
    else{
        ofSetColor(255, 0, 0);
        ofDrawBitmapString(ToFilename() + " " + ofToString(c), 10, 20);
    }
}


string ofApp::ToFilename(){
    switch (folder) {
        case 0:
            return "mask_A";
            break;
        case 1:
            return "mask_B";
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key >= '0' && key <= '9'){
        s->color = key - '0';
    }
    switch (key) {
        case 'p':
            bPlay = !bPlay;
            if(bPlay){
                c = 0;
                folder = 0;
                readFile();
            }
            else{
                
                ofSetFrameRate(30);
            }
            break;
            
        case ' ':
            c ++;
            saveFile();
            if (c > N) c = N;
            break;
            
        case '-':
            c --;
            if(c < 0) c = 0;
            break;
            
        case 'x':
            for(int i = 0; i < steps[c].size(); i++){
                if(ofPoint(mouseX, mouseY).distance (steps[c][i]->center) < 20){
                    steps[c].erase(steps[c].begin() + i);
                    break;
                }
            }
            break;
            
        case 'X':
            steps[c].clear();
            break;
            
        case '+':
            saveFile();
            folder += 1;
            folder = folder % 2;
            readFile();
            break;
            
            
        case 'c':
            if(c > 0)
                steps[c] = steps[c - 1];
            saveFile();
            break;
            
        case 'r':
            readFile();
            break;
            
        case '>':
            s->rotation += 10;
            break;
        case '<':
            s->rotation -= 10;
            break;
            
        case 'Z':
            s->scale += 1;
            break;
        case 'z':
            s->scale -= 1;
            s->scale = MAX(1, s->scale);
            break;
            
            
        case 'q':
            s->shape += 1;
            s->shape = MIN(shapes.size() - 1, s->shape);
            break;
        case 'a':
            s->shape -= 1;
            s->shape = MAX(0, s->shape);
            break;
            
        default:
            break;
    }
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    Shape *last = s;
    steps[c].push_back(s);
    bEdited = true;
    s = new Shape();
    s->colors = colors;
    s->shapes = shapes;
    
    s->shape = last->shape;
    s->color = last->color;
    s->scale = last->scale;
    s->rotation = last->rotation;
    
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

void ofApp::saveFile(){
    
    if(!bEdited) return;
    file.open(ToFilename() + ".txt", ofFile::WriteOnly);
    for(int j = 0; j < N; j ++){
        for(int i = 0; i < steps[j].size(); i++){
            Shape *p = steps[j][i];
            
            file << ofToString(j) << ";" << p->toString() << endl;
        }
    }
    file.close();
    bEdited = false;
    
}

void ofApp::readFile(){
    
    buffer = ofBufferFromFile(ToFilename() + ".txt");
    cout << ToFilename() + ".txt" << endl;
    for(int j = 0; j < N; j ++)
        steps[j].clear();
    
    for (auto line : buffer.getLines()){
        Shape *p = new Shape();
        p->colors = colors;
        p->shapes = shapes;
        
        vector<string> tokens = ofSplitString(line, ";");
        if(tokens.size() == 7){
            int j = ofToInt(tokens[0]);
            p->fromSring(line);
            if(j < N)
                steps[j].push_back(p);
        }
    }
}