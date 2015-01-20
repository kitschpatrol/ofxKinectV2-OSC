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
class Player{
public:
    Player();
    ~Player();
    void setup(string path);
    void update(ofEventArgs & args);
    void draw();
    vector<Skeleton> getSkeleton();
private:
    ofxXmlSettings file;
    bool bPlay;
    float startTime;
    float currentTime;
    float previousTime;
    float endTime;
    int numBodies;
    int numTags;
    int startTag;
    int endTag;
    map<string, Skeleton> bodies;
};