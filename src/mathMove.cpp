//
//  mathMove.cpp
//  frame3d
//
//  Created by 黃耀昌 on 2019/1/7.
//

#include "mathMove.hpp"

float Move::get(float time){
    return 1;
}

void Move::setSpaceDeepNess(float deepNess_){
    deepNess = deepNess_;
}

float SpiralMove::get(float time){
    float cycleTime = period;
    float currentRatio = fmod(time, cycleTime)/cycleTime;
    float target;
    float farRatio;
    
    if(currentRatio < peakRatio){
        target = currentRatio/peakRatio;
    }
    else{
        target = 1 - (currentRatio - peakRatio)/(1 - peakRatio);
    }
    
    farRatio = target * (upLet - lowLet) + lowLet;
    return farRatio;
    
    ofVec3f relativeCamPos;
    
    float time2Radiant = TWO_PI/period;
    
    float phase = ofGetElapsedTimef()*time2Radiant;
    
    relativeCamPos.x = cos(phase) * ofGetWidth()/2 * farRatio;
    relativeCamPos.z = sin(phase) * deepNess/2 * farRatio;
    relativeCamPos.y = ofGetHeight()/2;
}

void SpiralMove::setParameter(float period_, int cycleNum_){
    period = period_;
    cycleNum = cycleNum_;
}

//MoveControl::MoveControl(Move *move_){
//    move = move_;
//}

void MoveControl::setMovementType(Move *move_){
    move = move_;
}

float MoveControl::get(float time){
    return move->get(time);
}
