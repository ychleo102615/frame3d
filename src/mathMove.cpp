//
//  mathMove.cpp
//  frame3d
//
//  Created by 黃耀昌 on 2019/1/7.
//

#include "mathMove.hpp"

ofVec3f Move::get(float time){
    return ofVec3f(0,0,0);
}

void Move::setMoveRange(ofVec3f range_){
    range = range_;
}

void CircularMove::setParameter(float period_, int cycleNum_){
    period = period_;
    cycleNum = cycleNum_;
}

ofVec3f CircularMove::get(float time){
    
    float time2Radiant = TWO_PI*cycleNum/period;
    
    float phase = time*time2Radiant;
    
    ofVec3f camPos;
    camPos.x = cos(phase) * range.x/2;
    camPos.z = sin(phase) * range.z/2;
    camPos.y = 0;
    
    return camPos;
}

void SpiralMove::setParameter(float period_, int cycleNum_){
    period = period_;
    cycleNum = cycleNum_;
}

ofVec3f SpiralMove::get(float time){
    
    float currentRatio = fmod(time, period)/period;
    float targetRatio;
    float targetShiftedRatio;
    
    if(currentRatio < peakRatio){
        targetRatio = currentRatio/peakRatio;
    }
    else{
        targetRatio = 1 - (currentRatio - peakRatio)/(1 - peakRatio);
    }
    
    targetShiftedRatio = targetRatio * (upLet - lowLet) + lowLet;
    
    ofVec3f camPos;
    
//    float time2Radiant = TWO_PI*cycleNum/period;
//
//    float phase = time*time2Radiant;
//
//    camPos.x = cos(phase) * range.x/2 * targetShiftedRatio;
//    camPos.z = sin(phase) * range.z/2 * targetShiftedRatio;
//    camPos.y = 0;
    camPos = CircularMove::get(time) * targetShiftedRatio;
    
    
    return camPos;
}

void VibrateMove::setParameter(float period_){
    period = period_;
}

ofVec3f VibrateMove::get(float time){
    float c = cos(TWO_PI/period*time);
    return range*c/2;
}


void MoveControl::setMovementType(Move *move_){
    move = move_;
}

ofVec3f MoveControl::get(float time){
    return move->get(time);
}
