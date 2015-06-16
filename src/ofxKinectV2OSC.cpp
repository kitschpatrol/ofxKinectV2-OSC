#include "ofxKinectV2OSC.h"

void ofxKinectV2OSC::setup(int port) {
  isDebugEnabled = false;
  listeningPort = port;
  receiver.setup(listeningPort);
  mapper.mapTo(&skeletons);
  ofAddListener(mapper.newGesture, this, &ofxKinectV2OSC::triggerGesture);
}

void ofxKinectV2OSC::update() {
  parseOscMessages();
  clearStaleSkeletons();
}

void ofxKinectV2OSC::setSmoothing(SmoothingTechnique technique) {
  mapper.setSmoothing(technique);
}

void ofxKinectV2OSC::triggerGesture(Gesture &newGest) {
  ofNotifyEvent(newGesture, newGest, this);
}

vector<Skeleton> *ofxKinectV2OSC::getSkeletons() {
  return &skeletons;
}

Skeleton *ofxKinectV2OSC::getNearestSkeleton() {
  Skeleton *nearestSkeleton;
  for (int i = 0; i < skeletons.size(); i++) {
    if (i == 0 || skeletons.at(i).isCloserThan(nearestSkeleton)) {
      nearestSkeleton = &skeletons.at(i);
    }
  }
  return nearestSkeleton;
}

bool ofxKinectV2OSC::hasSkeletons() {
  return skeletons.size() > 0;
}

void ofxKinectV2OSC::parseOscMessages() {
  while (receiver.hasWaitingMessages()) {
    receiver.getNextMessage(&lastMessage);
    logger.log(lastMessage);
    mapper.map(lastMessage);
  }
}

void ofxKinectV2OSC::clearStaleSkeletons() {
  for (int i = 0; i < skeletons.size(); i++) {
    Skeleton *skeleton = &skeletons.at(i);
    skeleton->update();
    if (skeleton->isStale()) {
      skeletons.erase(skeletons.begin() + i);
    }
  }
}

void ofxKinectV2OSC::drawDebug() {
  if (isDebugEnabled) {
    string debug = buildDebugString();
    ofDrawBitmapString(debug, 60, 60);
  }
}

void ofxKinectV2OSC::toggleDebug() {
  isDebugEnabled = !isDebugEnabled;
}

string ofxKinectV2OSC::buildDebugString() {
  string debug = "DEBUG\n";

  if (logger.size() == 0) {
    debug.append("\nNo Kinect data received on OSC port " + ofToString(listeningPort) + "...try restarting the source");
  } else {
    debug.append(parseLogger());
  }
  return debug;
}

string ofxKinectV2OSC::parseLogger() {
  string parsed = "";
  for (int i = 0; i < logger.size(); i++) {
    parsed.append("\n" + logger.getLine(i));
  }
  return parsed;
}