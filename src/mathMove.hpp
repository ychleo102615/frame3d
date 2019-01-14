//
//  mathMove.hpp
//  frame3d
//
//  Created by 黃耀昌 on 2019/1/7.
//

#ifndef mathMove_hpp
#define mathMove_hpp

#include <stdio.h>
#include "ofMain.h"

#endif /* mathMove_hpp */

class Move{
public:
    virtual ofVec3f get(float time);
    Move(){};
    virtual ~Move(){};
    void setSpaceRange(float width_, float height_, float deepNess_);
    void setMoveRange(ofVec3f range);
    void setParameter();
    
    float width;
    float height;
    float deepNess;
};

class SpiralMove : public Move{
public:
    void setParameter(float period_, int cycleNum_);
    ofVec3f get(float time);
    SpiralMove(){};
    ~SpiralMove(){};
    
    float peakRatio = 0.9;
    float upLet = 1.3;
    float lowLet = 0.3;
    
    float period;
    int cycleNum;
};

class MoveControl{
public:
    Move *move;
    
    void setMovementType(Move *move_);
    ofVec3f get(float time);
};
