#pragma once
#include "ofMain.h"
#include "../Body/Skeleton.h"
#include "Parser.h"
#include "Gesture.h"
#include "ofxOscReceiver.h"

class Mapper {
public:
	void mapTo(vector<Skeleton>* skeletons);
	void map(ofxOscMessage &_message);
	void refresh();
	void setSmoothing(SmoothingTechnique technique);
    ofVec3f getFloorPlane();
    ofEvent<Gesture> newGesture;
    ofQuaternion getKinectOrientation();
protected:
	Skeleton* getSkeleton(string id);
	Skeleton* newSkeleton(string id);
	

	vector<Skeleton>* skeletons;
	Parser parser;
	SmoothingTechnique defaultSmoothing;
    ofVec3f floorNormal;
 
    unsigned long long diffTime;
};