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
    Move(){};
    virtual ~Move(){};
    virtual ofVec3f get(float time);
    void setMoveRange(ofVec3f range_);
    void setParameter();

//    float width;
//    float height;
//    float deepNess;
    ofVec3f range;
};

class CircularMove : public Move{
public:
    void setParameter(float period_, int cycleNum_);
    ofVec3f get(float time);
    
    float period;
    int cycleNum;
};

class SpiralMove : public CircularMove{//public Move{
public:
    void setParameter(float period_, int cycleNum_);
    ofVec3f get(float time);
    SpiralMove(){};
    ~SpiralMove(){};
    
    float peakRatio = 0.9;
    float upLet = 1.3;
    float lowLet = 0.3;
    
//    float period;
//    int cycleNum;
};

class VibrateMove : public Move{
public:
    void setParameter(float period_);
    ofVec3f get(float time);
    
    float period;
};

class SquareMove : public Move{
public:
    void setParameter(ofVec3f square_);
    ofVec3f get(float time);
    
};

class MoveControl{
public:
    Move *move;
    
    void setMovementType(Move *move_);
    ofVec3f get(float time);
};
