//
//  mathMove.cpp
//  frame3d
//
//  Created by 黃耀昌 on 2019/1/7.
//

#include "mathMove.hpp"

float SpiralMove::getTargetBy(float time, float cycleTime){
    float ratio = 0.9;
    float currentRatio = fmod(time, cycleTime)/cycleTime;
    
    if(currentRatio < ratio){
        return currentRatio/ratio;
    }
    else{
        return 1 - (currentRatio - ratio)/(1 - ratio);
    }
}

MoveControl::MoveControl(MathMove *move_){
    move = move_;
}

void MoveControl::setMovementType(MathMove *move_){
    move = move_;
}

float MoveControl::get(float t, float ct){
    return move->getTargetBy(t, ct);
}
