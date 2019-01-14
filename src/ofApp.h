#pragma once

#include "ofMain.h"
#include "spinFrame.hpp"
#include "mathMove.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofEasyCam easyCam;
    ofCamera cam;
    bool useCam;
    
    ofLight pointLight;
    ofLight directionalLight;
    ofMaterial material;
    
    ofVec3f hallCenter;
    
    SpiralMove sp;
    MoveControl mc;
    
    
    const float deepNess = 3000;//1000;
    const float cycleTime = 10;
    ofVec3f spaceRange;
    
    void drawBase(float size);
    void drawTestingCubes();
    void camMove();
};
