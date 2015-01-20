#pragma once
#include "ofMain.h"
#include "DataTransform/Logger.h"
#include "DataTransform/Mapper.h"
#include "Body/Skeleton.h"
#include "Draw/BodyRenderer.h"
#include "Recorder/Recorder.h"
#include "Recorder/Player.h"
class ofxKinectV2OSC {
public:
	void setup(int port, ofTrueTypeFont &_font, string file ="");
	void update();
	void setSmoothing(SmoothingTechnique technique);
    void setFont(ofTrueTypeFont _font);
	vector<Skeleton>* getSkeletons();
    Skeleton* getNearestSkeleton();
    bool hasSkeletons();
    void parseOscMessages();
    void clearStaleSkeletons();
	void drawDebug();
	void toggleDebug();
    void saveRecording();
protected:
	string buildDebugString();
	string parseLogger();

	ofxOscReceiver receiver;
	ofxOscMessage lastMessage;
	string lastParsedMessage;
	Logger logger;
	Mapper mapper;
	vector<Skeleton> skeletons;
	ofTrueTypeFont font;
	bool isDebugEnabled;
    bool playFromFile;
    Recorder recorder;
    Player  player;
};