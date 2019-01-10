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
    virtual float get(float time, float cycleTime);
    Move(){};
    virtual ~Move(){};
};

class SpiralMove : public Move{
public:
    float get(float time, float cycleTime);
    SpiralMove(){};
    ~SpiralMove(){};
    
    float peakRatio = 0.9;
    float upLet = 1.3;
    float lowLet = 0.3;
};

class MoveControl{
public:
    Move *move;
    
//    MoveControl(MathMove *move_);
    void setMovementType(Move *move_);
    float get(float time, float cycleTime);
};
