//
//  spinFrame.cpp
//  spinFrame
//
//  Created by 黃耀昌 on 2018/12/22.
//

#include "spinFrame.hpp"

Frame::Frame(ofVec3f center_, ofVec2f lv, int id_){
    id = id_;
    center = center_;
    lengthVector = lv;
    radiusVector = lengthVector/2;
    corner = -radiusVector;
    
    color = ofFloatColor::steelBlue;
    
    thickNessRatio = 0.03;
//    thickNessRatio = 0.1;
    thickNess = lengthVector.length() * thickNessRatio;
    edgeRatio = 0.8;
    build();
    
    initializePhysicalState();
    
    CircularMove::setParameter(ofVec3f(1,0,0), 4, 1);
    setMoveRange(ofVec3f(600,600,0));
}

void Frame::drawMeshFrame(){
    ofPushStyle();
    ofPushMatrix();
//    ofVec3f look = center + position;
    ofTranslate(center + get(ofGetElapsedTimef()+(float)id));
//    ofTranslate(center);
    ofRotateYDeg(rotateAngle);
    
    // ** Turn frame facing angle as how it is arranged
    ofRotateDeg(getAngle(), getCrossVector().x, getCrossVector().y, getCrossVector().z);
    
    
//    mesh.draw();
    material.begin();
    transformedMesh.draw();
    material.end();
//    mesh.drawWireframe();

    ofPopMatrix();
    ofPopStyle();
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
    transformedMesh = mesh;
    material.setDiffuseColor(color);
}

void Frame::buildNeededPlanes(){
    buildFrontAndBackPlanes();
    
    box.set(lengthVector.x, lengthVector.y, thickNess);
    innerBox.set(lengthVector.x*edgeRatio, lengthVector.y*edgeRatio, thickNess);
    
}

void Frame::buildFrontAndBackPlanes(){
    ofVec3f zOffset = ofVec3f(0, 0, -thickNess/2);
    ofVec3f insideEdgeCorner = corner+lengthVector*(1-edgeRatio)/2;
    
    pathFront.rectangle(corner+zOffset, lengthVector.x, lengthVector.y);
    pathFront.rectangle(insideEdgeCorner+zOffset, lengthVector.x*edgeRatio, lengthVector.y*edgeRatio);
    
    zOffset = ofVec3f(0, 0, thickNess/2);
    pathBack.rectangle(corner+zOffset, lengthVector.x, lengthVector.y);
    pathBack.rectangle(insideEdgeCorner+zOffset, lengthVector.x*edgeRatio, lengthVector.y*edgeRatio);
}

void Frame::buildMesh(){
    ofMesh lastMesh;
    mesh = pathFront.getTessellation();
    mesh.flatNormals();
    lastMesh = mesh;
    mesh.append(pathBack.getTessellation());
    mesh.flatNormals();
    flipNormal(mesh, lastMesh);
    
    // 0 and 3 means front and back
    mesh.append(box.getSideMesh(1));
    mesh.append(box.getSideMesh(2));
    mesh.append(box.getSideMesh(4));
    mesh.append(box.getSideMesh(5));
    lastMesh = mesh;
    
    mesh.append(innerBox.getSideMesh(1));
    mesh.append(innerBox.getSideMesh(2));
    mesh.append(innerBox.getSideMesh(4));
    mesh.append(innerBox.getSideMesh(5));
    
    flipNormal(mesh, lastMesh);
}


void Frame::flipNormal(ofMesh &mesh, ofMesh last){
    for(int i=last.getNumNormals(); i<mesh.getNumNormals();i++){
        mesh.setNormal(i, -mesh.getNormal(i));
    }
}


void Frame::update(){
    time++;
    rotateAngle += rotateSpeed;
    rotateSpeed += rotateForce;
    rotateForce = sin(time*radiusVector.x/360/30)*0.01;
    float p = 2000;
//    rotateForce = (fmod(time+id*10, p) > p/4 && fmod(time, p)<=3*p/4)?0.001:-0.001;
    transform();
}


void Frame::initializePhysicalState(){
    time = 0;
    rotateAngle = 0;
    rotateSpeed = 0;
    rotateForce = 0;
}


void Frame::transform(){
    
    float factor;
    
    factor = sin((time+id)/10)/2 + 1;
    
//    ofVec3f factorVector = ofVec3f(1,factor,1);
    ofVec3f factorVector = ofVec3f(0,factor*500,0);
    
    for(int i=0;i<mesh.getNumVertices();i++){
//        transformedMesh.setVertex(i, mesh.getVertex(i) * factor);
//        transformedMesh.setVertex(i, mesh.getVertex(i) + factorVector);
//        transformedMesh.setVertex(i, mesh.getVertex(i) * factorVector);
    }
}

void Frame::setAngle(float angle){
    rotateAngle = angle;
}

void Frame::setColor(ofColor c){
    color = c;
    material.setDiffuseColor(color);
}
