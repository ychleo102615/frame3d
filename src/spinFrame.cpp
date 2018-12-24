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
    thickNess = 200;
    edgeRatio = 0.8;
    build();
}

void Frame::drawMeshFrame(){
    ofPushStyle();
    ofSetColor(255);
    
    mesh.draw();
    ofSetColor(0);
    mesh.drawWireframe();

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

void Frame::setCorLen(ofVec3f c, ofVec2f lv){
    
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
