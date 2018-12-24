#include "ofApp.h"

vector<Frame> frames;

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ofVec3f corner = ofVec3f(-500, -350, 0);
    ofVec2f lengthVector = ofVec2f(1000, 700);
    
    frames.push_back(Frame(corner, lengthVector));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(50), ofColor(200), OF_GRADIENT_CIRCULAR);
    
    easyCam.begin();
    drawBase(1000);
    
    for(int i=0;i<frames.size();i++){
        frames.at(i).drawMeshFrame();
//        frames.at(i).drawPathFrame();
    }
    
    ofSetColor(200, 100, 100);
    
    easyCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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


void ofApp::drawBase(float size){
    ofPushStyle();
    ofSetColor(ofColor::red);
    ofDrawLine(0, 0, 0, size, 0, 0);
    ofSetColor(ofColor::green);
    ofDrawLine(0, 0, 0, 0, size, 0);
    ofSetColor(ofColor::blue);
    ofDrawLine(0, 0, 0, 0, 0, size);
}
