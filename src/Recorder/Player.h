//
//  Player.h
//  example
//
//  Created by dantheman on 1/20/15.
//
//

#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "../Body/Skeleton.h"
#include "../Body/Joint.h"
#include "../Body/Hand.h"
#include "ofxOsc.h"
class Player :public ofThread{
public:
    Player();
    ~Player();
    void setup(string path);
    void start();
    void stop();
    void threadedFunction();
private:
    ofxXmlSettings file;
    bool bPlay;
    unsigned long long  startTime;
    unsigned long long  currentTime;
    unsigned long long  previousTime;
    unsigned long long duration;
    int numBodies;
    int numTags;
    int startTag;
    int endTag;
    map<unsigned long long, string > timeCodedPaths;
    ofxOscSender sender;
};