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

class MathMove{
public:
    float getTargetBy(float time, float cycleTime);
};

class SpiralMove : public MathMove{
public:
    float getTargetBy(float time, float cycleTime);
};

class MoveControl{
public:
    MathMove *move;
    
    MoveControl(MathMove *move_);
    void setMovementType(MathMove *move_);
    float get(float t, float ct);
};
