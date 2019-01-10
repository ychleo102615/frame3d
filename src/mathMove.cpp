//
//  mathMove.cpp
//  frame3d
//
//  Created by 黃耀昌 on 2019/1/7.
//

#include "mathMove.hpp"

float SpiralMove::get(float time, float cycleTime){
    
    float currentRatio = fmod(time, cycleTime)/cycleTime;
    float target;
    
    if(currentRatio < peakRatio){
        target = currentRatio/peakRatio;
    }
    else{
        target = 1 - (currentRatio - peakRatio)/(1 - peakRatio);
    }
    
    return target * (upLet - lowLet) + lowLet;
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
