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

void Move::setSpaceRange(float width_, float height_, float deepNess_){
    width = width_;
    height = height_;
    deepNess = deepNess_;
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
    
    ofVec3f relativeCamPos;
    
    float time2Radiant = TWO_PI*cycleNum/period;
    
    float phase = time*time2Radiant;
    
    relativeCamPos.x = cos(phase) * width/2 * targetShiftedRatio;
    relativeCamPos.z = sin(phase) * deepNess/2 * targetShiftedRatio;
    relativeCamPos.y = 0;
    
    
    return relativeCamPos;
}

//MoveControl::MoveControl(Move *move_){
//    move = move_;
//}

void MoveControl::setMovementType(Move *move_){
    move = move_;
}

ofVec3f MoveControl::get(float time){
    return move->get(time);
}
