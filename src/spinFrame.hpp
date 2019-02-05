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
#include "mathMove.hpp"

#endif /* spinFrame_hpp */

class Frame : public CircularMove{
private:
    ofVec3f center;
    ofVec3f corner;
    ofVec2f lengthVector;
    ofVec2f radiusVector;
    
    ofMesh mesh;
    ofMesh transformedMesh;
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
    
    ofFloatColor color;
    ofMaterial material;
    
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
    
    void flipNormal(ofMesh &mesh, ofMesh last);
    
    void transform();
    void setAngle(float angle);
    void setColor(ofColor c);
};
