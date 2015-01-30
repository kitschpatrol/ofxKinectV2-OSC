#pragma once

#include "ofMain.h"
#include "ofxKinectV2OSC.h"
#include "ofxGui.h"
#include "ofxMidi.h"


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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxKinectV2OSC kinect;
		Skeleton* skeleton;
		vector<Skeleton>* skeletons;
		ofTrueTypeFont smallFont, largeFont;

		BodyRenderer renderer;
    
        ofEasyCam cam;
        ofxPanel gui;
    
    
        ofParameter <ofVec3f> boxDim;
        ofParameter <ofVec3f> boxPosStart;
        ofParameter <ofVec3f> boxPosEnd;
        ofParameter < int > nDivisions;
    
        ofParameter <ofVec3f> scale;
        ofParameter <float> rotationX;
        ofParameter <float> rotationY;
        ofParameter <float> rotationZ;
        ofParameter <ofVec3f> offset;
    
        vector < bool > bInside;
    
        bool bPointInsideBox(ofPoint startPos, ofPoint endPos, ofPoint pt);
    
    
        ofxMidiOut midi;
    
    
    ofSerial ser;
    
    
};