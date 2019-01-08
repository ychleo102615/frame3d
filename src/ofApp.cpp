#include "ofApp.h"

vector<Frame> frames;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ofSetSmoothLighting(true);
    
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 0.f));
    pointLight.setPointLight();
    directionalLight.setDiffuseColor(ofColor(0.f, 0.f, 255.f));
    directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
    directionalLight.setDirectional();
    directionalLight.setOrientation( ofVec3f(0, 90, 0) );

    
    material.setShininess(120);
    material.setSpecularColor(ofColor(255,255,255,255));
    
    
//    for(int i=0;i<10;i++){
//        ofVec3f center = ofVec3f(ofRandomWidth(), ofRandomHeight(), ofRandom(1000));
//        ofVec2f lengthVector = ofVec2f(ofRandomWidth(), ofRandomHeight());
//        frames.push_back(Frame(center, lengthVector));
//    }
    
    for(int i=0;i<24;i++){
//        ofVec3f center = ofVec3f(0,0,0);
        ofVec3f center = ofVec3f(ofRandomWidth(), ofRandomHeight(), ofRandom(1000));
//        ofVec2f lengthVector = ofVec2f(70*(i+1), 50*(i+1));
        ofVec2f lengthVector = ofVec2f(70*pow(1.5, (i+1)/5), 50*pow(1.5, (i+1)/5));
        frames.push_back(Frame(center, lengthVector));
    }
    
    
    cam.setPosition(0, 0, 0);
    cam.lookAt(ofVec3f(ofGetWidth(), ofGetHeight(), 1000));
    useCam = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0;i<frames.size();i++){
        frames.at(i).update();
    }
    
    pointLight.setPosition(0, cos(ofGetElapsedTimef()*.6f)*1000, sin(ofGetElapsedTimef()*.6f)*1000);
    
    camMove();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(50), ofColor(200), OF_GRADIENT_CIRCULAR);
//    glEnable(GL_CULL_FACE);
    
    if(useCam)
        cam.begin();
    else
        easyCam.begin();
    
    ofEnableLighting();
    material.begin();
    pointLight.enable();
    directionalLight.enable();
    
    
    drawBase(1000);
    
    for(int i=0;i<frames.size();i++){
        frames.at(i).drawMeshFrame();
    }
    
    
    drawTestingCubes();
    
    ofDisableLighting();
    material.end();
    
    ofSetColor(200, 100, 100);
    ofDrawSphere(pointLight.getPosition(), 20);
    
    if(useCam)
        cam.end();
    else
        easyCam.end();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ')
        useCam = !useCam;
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
    ofPopStyle();
    
}

void ofApp::drawTestingCubes(){
    
    // testing cube
    int cubeLength = 100;
    ofDrawBox(0, 0, -500, cubeLength);
    ofDrawBox(0, 0, -1200, cubeLength*5);
    
    ofDrawBox(0, cos(ofGetElapsedTimef()*.6f)*360, -500, cubeLength);
    
    ofPushMatrix();
    ofTranslate(300, cos(ofGetElapsedTimef()*.6f)*360, -500);
    ofRotateYDeg(ofGetFrameNum());
    ofDrawBox(0, 0, 0, cubeLength);
    ofPopMatrix();
    
    ofMesh mesh;
    ofBoxPrimitive box = ofBoxPrimitive(cubeLength,cubeLength,cubeLength);
    ofBoxPrimitive innerBox = ofBoxPrimitive(cubeLength*0.5,cubeLength*0.5,cubeLength*0.5);
    //    for(int i=0;i<6;i++)
    //        mesh.append(box.getSideMesh(i));
    mesh.append(box.getSideMesh(1));
    mesh.append(box.getSideMesh(2));
    mesh.append(box.getSideMesh(4));
    mesh.append(box.getSideMesh(5));
    
    mesh.append(innerBox.getSideMesh(1));
    mesh.append(innerBox.getSideMesh(2));
    mesh.append(innerBox.getSideMesh(4));
    mesh.append(innerBox.getSideMesh(5));
    ofPushMatrix();
    ofTranslate(600, cos(ofGetElapsedTimef()*.6f)*360, 0);
    mesh.draw();
    ofPopMatrix();
    mesh.clear();
    
    ofPath testPath;
    testPath.rectangle(-cubeLength/2, -cubeLength/2, cubeLength, cubeLength);
    mesh = testPath.getTessellation();
    mesh.flatNormals();
    mesh.draw();
}

void ofApp::camMove(){
    
//    SpiralMove sp;
//    MoveControl mc;
//    MoveControl mc = *new MoveControl(&sp);
    mc.setMovementType(&sp);
    float farRatio = mc.get(ofGetElapsedTimef(), cycleTime);
    cout << "farRatio: " << farRatio << " in " << ofGetElapsedTimef() << endl;
    
    
    float camX, camY, camZ;
    float ratio = fmod(ofGetElapsedTimef(), cycleTime)/cycleTime;
    float time2Radiant = TWO_PI/cycleTime;
    camX = (1-cos(ofGetElapsedTimef()*time2Radiant)) * ofGetWidth()/2 * ratio;
    camZ = (1-sin(ofGetElapsedTimef()*time2Radiant)) * deepNess/2 * ratio;
    float oscilationPeriod = 2.0;
    camY = (1-cos(ofGetElapsedTimef()/oscilationPeriod * TWO_PI)) * ofGetHeight()/2/5 + ofGetHeight()/2;
    
    
    ofVec3f camPos = ofVec3f(camX, camY, camZ);
    cam.setPosition(camPos);
    cam.lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, deepNess/2));
}
