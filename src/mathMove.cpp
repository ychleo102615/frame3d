//
//  mathMove.cpp
//  frame3d
//
//  Created by 黃耀昌 on 2019/1/7.
//

#include "mathMove.hpp"

float SpiralMove::get(float time, float cycleTime){
    float ratio = 0.9;
    float currentRatio = fmod(time, cycleTime)/cycleTime;
    
    if(currentRatio < ratio){
        return currentRatio/ratio;
    }
    else{
        return 1 - (currentRatio - ratio)/(1 - ratio);
    }
}

float Move::get(float time, float cycleTime){
    return 1;
}

//MoveControl::MoveControl(Move *move_){
//    move = move_;
//}

void MoveControl::setMovementType(Move *move_){
    move = move_;
}

float MoveControl::get(float time, float cycleTime){
    return move->get(time, cycleTime);
}
