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
    virtual float get(float time);
    Move(){};
    virtual ~Move(){};
    void setSpaceDeepNess(float deepNess_);
    void setParameter();
    
    float deepNess;
};

class SpiralMove : public Move{
public:
    float get(float time);
    SpiralMove(){};
    ~SpiralMove(){};
    void setParameter(float period_, int cycleNum_);
    
    
    float peakRatio = 0.9;
    float upLet = 1.3;
    float lowLet = 0.3;
    
    float period;
    int cycleNum;
};

class MoveControl{
public:
    Move *move;
    
//    MoveControl(MathMove *move_);
    void setMovementType(Move *move_);
    float get(float time);
};
