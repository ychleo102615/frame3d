#include "ofApp.h"

vector<Frame> frames;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ofSetSmoothLighting(true);
    
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    pointLight.setPointLight();
    directionalLight.setDiffuseColor(ofColor(255.f, 255.f, 255.f));
    directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
    directionalLight.setDirectional();
    directionalLight.setOrientation( ofVec3f(0, 90, 0) );

    
    material.setShininess(120);
    material.setSpecularColor(ofColor(255,255,255,255));
    
    spaceRange = ofVec3f(ofGetWidth()*3, ofGetHeight()*3, deepNess);
    
//    hallCenter = spaceRange/2;
    hallCenter = ofVec3f(0,spaceRange.y/2,deepNess/2);
    
    /*
    for(int i=0;i<100;i++){//24
        
        ofVec2f lengthVector = ofVec2f(700, 500);
//        ofVec2f lengthVector = ofVec2f(70*pow(1.5, (i+1)/5), 50*pow(1.5, (i+1)/5));
//        float r = ofRandom(30);
//        ofVec2f lengthVector = ofVec2f(70*pow(1.5, (r+1)/5), 50*pow(1.5, (r+1)/5));
        frames.push_back(Frame(frameCenter, lengthVector, i));
    }*/
    
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            ofVec2f lengthVector = ofVec2f(500, 500);
            ofVec3f frameCenter = ofVec3f(800*i-4000, spaceRange.y/2, 400*j);
//            ofVec3f frameCenter = ofVec3f(1600*i-4000, spaceRange.y/2, 800*j);
            frames.push_back(Frame(frameCenter, lengthVector, i*10+j));
        }
    }
    
    
    // Setting camera move rule, check camMove()
    sp.setMoveRange(spaceRange);
    sp.setParameter(ofVec3f(0,1,0), cycleTime, 2);
    mcSpiral.setMovementType(&sp);
    vb.setMoveRange(ofVec3f(0, spaceRange.y/10, 0));
    vb.setParameter(2.0);
    mcVibrate.setMovementType(&vb);
    
    cam.setPosition(0, 0, 0);
    cam.lookAt(hallCenter);
    useCam = true;
    spinTogether = false;
    drawTrail = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofColor rb = ofColor::darkMagenta;
    ofColor target = ofColor::goldenRod;
    for(int i=0;i<frames.size();i++){
        if(spinTogether)
            frames.at(i).setAngle((fmod(ofGetElapsedTimef(),cycleTime))*360/cycleTime);
        else
            frames.at(i).update();
        
        float colorSeed = ofGetElapsedTimef()*10+i;
        
        int channel = 10;
        int colorPeriod = i%channel+1;
//        float lerp = (sin(fmod(ofGetElapsedTimef(),colorPeriod)*TWO_PI/colorPeriod)+1)/2;
        float lerp = (float)(i%channel)/(channel - 1);
        ofColor c = rb.getLerped(target, lerp);
        
        frames.at(i).setColor(c);
    }
        
    
    pointLight.setPosition(0, cos(ofGetElapsedTimef()*.6f)*1000, sin(ofGetElapsedTimef()*.6f)*1000);
    
    float phase = ofGetElapsedTimef()*TWO_PI/cycleTime;
//    sp.setTargetPlane(ofVec3f(cos(phase)/2, 1, sin(phase)/2));
    camMove();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(50), ofColor(100), OF_GRADIENT_CIRCULAR);
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
    ofPushMatrix();
    for(int k=0;k<10;k++){
//        ofRotateZDeg(90);
//        ofRotateXDeg(36);
        ofTranslate(0, 600, 0);
        for(int i=0;i<frames.size();i++){
            frames.at(i).drawMeshFrame();
        }
    }
    
    ofPopMatrix();
    
    
    drawTestingCubes();
    
    ofSetColor(0, 228, 255);
    ofDrawSphere(hallCenter, 20);
    
    ofDisableLighting();
    material.end();
    
    ofSetColor(200, 100, 100);
    ofDrawSphere(pointLight.getPosition(), 20);
    
    if(drawTrail)
        showCameraTrail();
    
    if(useCam)
        cam.end();
    else
        easyCam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ')
        useCam = !useCam;
    if(key == 's')
        spinTogether = !spinTogether;
    if(key == 't')
        drawTrail = !drawTrail;
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

    ofVec3f camPos = hallCenter + mcSpiral.get(ofGetElapsedTimef());// + mcVibrate.get(ofGetElapsedTimef());
    

    
    cam.setPosition(camPos);
    cam.lookAt(hallCenter);
}

void ofApp::showCameraTrail(){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(hallCenter);
    ofSetColor(ofColor::sandyBrown, 50);
    ofVec3f rotate = sp.getCrossVector();
    ofRotateDeg(sp.getAngle(), rotate.x, rotate.y, rotate.z);
    ofDrawEllipse(0,0,0, spaceRange.x, spaceRange.y);
    ofPopMatrix();
    ofVec3f pos = cam.getPosition();
    ofDrawSphere(pos, 100);
    ofPopStyle();
}
