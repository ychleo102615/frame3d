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
//    thickNessRatio = 0.1;
    thickNess = lengthVector.length() * thickNessRatio;
    edgeRatio = 0.8;
    build();
    
    initializePhysicalState();
}

void Frame::drawMeshFrame(){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(center);
    ofRotateYDeg(rotateAngle);
    
//    mesh.draw();
    presentMesh.draw();
//    ofSetColor(0);
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
    presentMesh = mesh;
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
    transform();
}


void Frame::initializePhysicalState(){
    time = 0;
    rotateAngle = 0;
    rotateSpeed = 0;
    rotateForce = 0;
}


void Frame::addSurfaceNormalsToMesh(ofMesh &mesh) {
    
    for (int i=0; i<mesh.getNumVertices(); i+=3) {
        
        ofVec3f v0 = mesh.getVertex(mesh.getIndex(i));
        ofVec3f v1 = mesh.getVertex(mesh.getIndex(i+1));
        ofVec3f v2 = mesh.getVertex(mesh.getIndex(i+2));
        
        ofVec3f U = v1 - v0;
        ofVec3f V = v2 - v0;
        
        float x = (U.y * V.z) - (U.z * V.y);
        float y = (U.z * V.x) - (U.x * V.z);
        float z = (U.x * V.y) - (U.y * V.x);
        
        ofVec3f normal(x,y,z);
        
        normal.normalize();
        
        mesh.addNormal(normal);
        mesh.addNormal(normal);
        mesh.addNormal(normal);
    }
}


void Frame::transform(){
    
    float factor;
    
    factor = sin(time/10)/10 + 1;
    
    for(int i=0;i<mesh.getNumVertices();i++){
        presentMesh.setVertex(i, mesh.getVertex(i) * factor);
    }
}
