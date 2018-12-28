//
//  spinFrame.cpp
//  spinFrame
//
//  Created by 黃耀昌 on 2018/12/22.
//

#include "spinFrame.hpp"

Frame::Frame(ofVec3f center_, ofVec2f lv){
    center = center_;
    lengthVector = lv;
    radiusVector = lengthVector/2;
    corner = -radiusVector;
    
    thickNessRatio = 0.03;
    thickNess = lengthVector.length() * thickNessRatio;
    edgeRatio = 0.8;
    build();
    
    phase = 0;
    spinSpeed = radiusVector.getNormalized().x * 4;
    
    initializePhysicalState();
}

void Frame::drawMeshFrame(){
//    ofPushStyle();
    ofPushMatrix();
    ofTranslate(center);
    ofRotateYDeg(rotateAngle);
//    ofSetColor(255);
    
    mesh.draw();
//    ofSetColor(0);
//    mesh.drawWireframe();

    ofPopMatrix();
//    ofPopStyle();
}

void Frame::drawPathFrame(){
    ofPushStyle();
    ofSetColor(255);
    ofNoFill();
    
    pathFront.draw();
    pathBack.draw();

    ofPopStyle();
}

void Frame::build(){
    buildNeededPlanes();
    buildMesh();
}

void Frame::buildNeededPlanes(){
    buildFrontAndBackPlanes();
    
    box.set(lengthVector.x, lengthVector.y, thickNess);
    innerBox.set(lengthVector.x*edgeRatio, lengthVector.y*edgeRatio, thickNess);
    
}

void Frame::buildFrontAndBackPlanes(){
    ofVec3f zOffset = ofVec3f(0, 0, thickNess/2);
    ofVec3f insideEdgeCorner = corner+lengthVector*(1-edgeRatio)/2;
    
    pathFront.rectangle(corner+zOffset, lengthVector.x, lengthVector.y);
    pathFront.rectangle(insideEdgeCorner+zOffset, lengthVector.x*edgeRatio, lengthVector.y*edgeRatio);
    
    zOffset = ofVec3f(0, 0, -thickNess/2);
    pathBack.rectangle(corner+zOffset, lengthVector.x, lengthVector.y);
    pathBack.rectangle(insideEdgeCorner+zOffset, lengthVector.x*edgeRatio, lengthVector.y*edgeRatio);
}

void Frame::buildMesh(){
    mesh = pathFront.getTessellation();
    mesh.append(pathBack.getTessellation());
    
    // 0 and 3 means front and back
    mesh.append(box.getSideMesh(1));
    mesh.append(box.getSideMesh(2));
    mesh.append(box.getSideMesh(4));
    mesh.append(box.getSideMesh(5));
    
    mesh.append(innerBox.getSideMesh(1));
    mesh.append(innerBox.getSideMesh(2));
    mesh.append(innerBox.getSideMesh(4));
    mesh.append(innerBox.getSideMesh(5));
}

void Frame::update(){
    phase += spinSpeed;
    
    time++;
    rotateAngle += rotateSpeed;
    rotateSpeed += rotateForce;
    rotateForce = sin(time*radiusVector.x/360/30)*0.01;
    
}

void Frame::initializePhysicalState(){
    time = 0;
    rotateAngle = 0;
    rotateSpeed = 0;
    rotateForce = 0;
}
