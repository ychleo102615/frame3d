//
//  spinFrame.cpp
//  spinFrame
//
//  Created by 黃耀昌 on 2018/12/22.
//

#include "spinFrame.hpp"

Frame::Frame(ofVec3f c, ofVec2f lv){
    corner = c;
    lengthVector = lv;
    mesh.setMode( OF_PRIMITIVE_LINE_LOOP);
    buildPath();
    buildMesh();
}

void Frame::drawFrame(){
    ofPushStyle();
    ofSetColor(255);
    ofNoFill();
    ofDrawRectangle(corner, lengthVector.x, lengthVector.y);
    ofPopStyle();
}

void Frame::drawMeshFrame(){
    ofPushStyle();
    ofSetColor(255);
    ofNoFill();
    
    mesh.draw();
//    mesh.drawWireframe();

    ofPopStyle();
}

void Frame::drawPathFrame(){
    ofPushStyle();
    ofSetColor(255);
    ofNoFill();
    
    path.draw();
    pathBack.draw();

    ofPopStyle();
}

void Frame::setCorLen(ofVec3f c, ofVec2f lv){
    
}

void Frame::buildPath(){
    path.rectangle(corner, lengthVector.x, lengthVector.y);
    path.rectangle(corner+lengthVector/10, lengthVector.x*8/10, lengthVector.y*8/10);
    
    ofVec3f zOffset = ofVec3f(0, 0, 200);
    pathBack.rectangle(corner+zOffset, lengthVector.x, lengthVector.y);
    pathBack.rectangle(corner+zOffset+lengthVector/10, lengthVector.x*8/10, lengthVector.y*8/10);
}

void Frame::buildMesh(){
    
    ofVec3f xOffset = ofVec3f(lengthVector.x, 0, 0);
    ofVec3f yOffset = ofVec3f(0, lengthVector.y, 0);
    ofVec3f zOffset = ofVec3f(0, 0, 200);
    
    //    mesh.addVertex(corner);
    //    mesh.addVertex(corner+xOffset);
    //    mesh.addVertex(corner+lengthVector);
    //    mesh.addVertex(corner+yOffset);
    mesh = path.getTessellation();
    ofBoxPrimitive box;
    box.set(lengthVector.x, lengthVector.y, 400);
    mesh.append(box.getSideMesh(1));
    mesh.append(box.getSideMesh(2));
    mesh.append(box.getSideMesh(4));
    mesh.append(box.getSideMesh(5));
    
//    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
}
