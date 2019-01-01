//
//  spinFrame.hpp
//  spinFrame
//
//  Created by 黃耀昌 on 2018/12/22.
//

#ifndef spinFrame_hpp
#define spinFrame_hpp

#include <stdio.h>
#include "ofMain.h"

#endif /* spinFrame_hpp */

class Frame{
private:
    ofVec3f center;
    ofVec3f corner;
    ofVec2f lengthVector;
    ofVec2f radiusVector;
    
    ofMesh mesh;
    ofMesh presentMesh;
    ofPath pathFront;
    ofPath pathBack;
    ofBoxPrimitive box;
    ofBoxPrimitive innerBox;
    
    float rotateAngle;
    float rotateSpeed;
    float rotateForce;
    float time;
    
    
    float thickNess;
    float thickNessRatio;
    float edgeRatio;
    
public:
    Frame(ofVec3f center_, ofVec2f lv);
    void drawMeshFrame();
    void drawPathFrame();
    
    void build();
    void buildNeededPlanes();
    void buildFrontAndBackPlanes();
    void buildMesh();
    
    void update();
    void initializePhysicalState();
    
    void addSurfaceNormalsToMesh(ofMesh &mesh);
    void flipNormal(ofMesh &mesh, ofMesh last);
    
    void transform();
};
