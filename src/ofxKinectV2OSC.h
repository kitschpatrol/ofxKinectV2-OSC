#pragma once

#include "ofMain.h"
#include "DataTransform/Logger.h"
#include "DataTransform/Mapper.h"
#include "Body/Skeleton.h"
#include "Draw/BodyRenderer.h"

class ofxKinectV2OSC {
public:
  void setup(int port);
  void update();
  void setSmoothing(SmoothingTechnique technique);
  vector<Skeleton> *getSkeletons();
  Skeleton *getNearestSkeleton();
  bool hasSkeletons();
  void parseOscMessages();
  void clearStaleSkeletons();
  void drawDebug();
  void toggleDebug();
  void triggerGesture(Gesture &newGest);
  ofEvent<Gesture> newGesture;

protected:
  string buildDebugString();
  string parseLogger();

  
  int listeningPort;
  ofxOscReceiver receiver;
  ofxOscMessage lastMessage;
  string lastParsedMessage;
  Logger logger;
  Mapper mapper;
  vector<Skeleton> skeletons;
  bool isDebugEnabled;
};