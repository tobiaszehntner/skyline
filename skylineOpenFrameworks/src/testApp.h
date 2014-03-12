#pragma once

#include "ofMain.h"




class KeyFrame
{
public:
    ofImage pixels;
    unsigned long long timestamp;
    
};



class testApp : public ofBaseApp{

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    std::vector<KeyFrame> keyFrames;
    
    int numPixels;
    
    int minTime;
    int maxTime;
    
    int minRGBvalue;
    int maxRGBvalue;
		
};
