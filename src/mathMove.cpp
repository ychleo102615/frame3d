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


void CircularMove::setParameter(ofVec3f normalVector_, float period_, int cycleNum_){
    period = period_;
    cycleNum = cycleNum_;
    normalVector = normalVector_;
    targetNormalVector = normalVector_;
}

ofVec3f CircularMove::get(float time){
    
    float time2Radiant = TWO_PI*cycleNum/period;
    float phase = time*time2Radiant;
    
    position = ofVec3f(cos(phase), sin(phase), 0);
    position *= range/2;
//    targetNormalVector.rotate(ofGetElapsedTimef()/10, ofVec3f(1,0,0));
    rotate2TargetPlane();
    
    return position;
}

ofVec3f CircularMove::getCrossVector(){
    return baseNormalVector.getCrossed(targetNormalVector);
}

void CircularMove::rotate2TargetPlane(){
    ofVec3f rotateAxis = getCrossVector();
    float angle = targetNormalVector.angle(baseNormalVector);
    position.rotate(angle, rotateAxis);
}

void CircularMove::setTargetPlane(ofVec3f targetNormalVector_){
    targetNormalVector = targetNormalVector_;
}

void SpiralMove::setParameter(ofVec3f normalVector_, float period_, int cycleNum_){
    CircularMove::setParameter(normalVector_, period_, cycleNum_);
    
    setPeakAndPeriod(0.9, period_);
}

ofVec3f SpiralMove::get(float time){
//    ofVec3f position;
    position = CircularMove::get(time) * getUndulation(time);
    
    return position;
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

void Undulation::setPeakAndPeriod(float peakRatio_, float period_){
    
    setPeakRatio(peakRatio_);
    setPeriods(period_);
}

void Undulation::setPeakRatio(float peakRatio_){
    peakRatio = peakRatio_;
}

void Undulation::setPeriods(float period_){
    periodUndu = period_;
    prePeriod = periodUndu * peakRatio;
    complementPeriod = periodUndu - prePeriod;
}

float Undulation::getUndulation(float time){
    
    currentTime = fmod(time, periodUndu);
    if(currentTime < prePeriod){
        phase = currentTime*(PI/prePeriod);
    }
    else {
        phase = (currentTime-prePeriod)*(PI/complementPeriod) + PI;
    }
    
    
    targetRatio = (1 - cos(phase)) / 2;
    targetShiftedRatio = targetRatio * (upLet - lowLet) + lowLet;
    
    return targetShiftedRatio;
}
