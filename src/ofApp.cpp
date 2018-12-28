#include "ofApp.h"

vector<Frame> frames;

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ofSetSmoothLighting(true);
    
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 0.f));
    pointLight.setPointLight();
    
    material.setShininess(120);
    material.setSpecularColor(ofColor(255,255,255,255));
    
//    ofVec3f center = ofVec3f(-500, -350, 0);
//    ofVec2f lengthVector = ofVec2f(1000, 700);
//
//    ofVec3f center2 = ofVec3f(0,0,0);
//    ofVec2f lengthVector2 = ofVec2f(1500, 1000);
//
//    ofVec3f center3 = ofVec3f(-500, -350, 1000);
//    ofVec2f lengthVector3 = ofVec2f(2100, 2700);
//
//    frames.push_back(Frame(center, lengthVector));
//    frames.push_back(Frame(center2, lengthVector2));
//    frames.push_back(Frame(center3, lengthVector3));
    
//    for(int i=0;i<10;i++){
//        ofVec3f center = ofVec3f(ofRandomWidth(), ofRandomHeight(), ofRandom(1000));
//        ofVec2f lengthVector = ofVec2f(ofRandomWidth(), ofRandomHeight());
//        frames.push_back(Frame(center, lengthVector));
//    }
    
    for(int i=0;i<1;i++){
        ofVec3f center = ofVec3f(100,100,100);
//        ofVec3f center = ofVec3f(ofRandomWidth(), ofRandomHeight(), ofRandom(1000));
        ofVec2f lengthVector = ofVec2f(700*(i+1), 500*(i+1));
        frames.push_back(Frame(center, lengthVector));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0;i<frames.size();i++){
        frames.at(i).update();
    }
    
    pointLight.setPosition(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(50), ofColor(200), OF_GRADIENT_CIRCULAR);
    
    easyCam.begin();
    
    ofEnableLighting();
    material.begin();
    pointLight.enable();
    
    
    
    drawBase(1000);
    
    for(int i=0;i<frames.size();i++){
        frames.at(i).drawMeshFrame();
//        frames.at(i).drawPathFrame();
    }
    
    ofSetColor(200, 100, 100);
    
    ofDrawBox(0, 0, -500, 100);
    ofDrawBox(0, 0, -1200, 500);
    
    ofDrawBox(0, cos(ofGetElapsedTimef()*.6f)*360, -500, 100);
    
    ofPushMatrix();
    ofTranslate(0, cos(ofGetElapsedTimef()*.6f)*360, 0);
    ofDrawBox(300, 0, -500, 100);
    ofPopMatrix();
    
    ofDisableLighting();
    material.end();
    
    ofDrawSphere(0, 0, 0, 20);
    
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
