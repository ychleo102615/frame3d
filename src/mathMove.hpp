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
    Move(){};
    virtual ~Move(){};
    virtual ofVec3f get(float time);
    void setMoveRange(ofVec3f range_);
    void setParameter();

    ofVec3f range;
    ofVec3f position;
};

class Undulation{
public:
    float peakRatio;
    float upLet = 1.1;
    float lowLet = 0.1;
    
    float prePeriod;
    float complementPeriod;
    float periodUndu;
    
    float phase;
    float currentTime;
    float targetRatio;
    float targetShiftedRatio;
    
    void setPeakAndPeriod(float peakRatio_, float period_);
    void setPeakRatio(float peakRatio_);
    void setPeriods(float period_);
    float getUndulation(float time);
};


class CircularMove : public Move{
public:
    void setParameter(ofVec3f normalVector_, float period_, int cycleNum_);
    ofVec3f get(float time);
    ofVec3f getCrossVector();
    float getAngle();
    void rotate2TargetPlane();
    void setTargetPlane(ofVec3f targetNormalVector_);
    
    float period;
    int cycleNum;
    
    ofVec3f normalVector;
    ofVec3f baseNormalVector = ofVec3f(0,0,1);
    ofVec3f targetNormalVector = ofVec3f(0,1,0);
    
};

class SpiralMove : public CircularMove, public Undulation{//public Move{
public:
    SpiralMove(){};
    ~SpiralMove(){};
    void setParameter(ofVec3f normalVector_, float period_, int cycleNum_);
    ofVec3f get(float time);
    

};

class VibrateMove : public Move{
public:
    void setParameter(float period_);
    ofVec3f get(float time);
    
    float period;
};

class SquareMove : public Move{
public:
    void setParameter(ofVec3f square_);
    ofVec3f get(float time);
    
};

class MoveControl{
public:
    Move *move;
    
    void setMovementType(Move *move_);
    ofVec3f get(float time);
};

