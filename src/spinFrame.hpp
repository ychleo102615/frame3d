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
    ofVec3f corner;
    ofVec2f lengthVector;
    ofMesh mesh;
    ofPath path;
    ofPath pathBack;
    
public:
    Frame(ofVec3f c, ofVec2f l);
    void setCorLen(ofVec3f c, ofVec2f lv);
    void drawFrame();
    void drawMeshFrame();
    void drawPathFrame();
    void buildMesh();
    void buildPath();
};
