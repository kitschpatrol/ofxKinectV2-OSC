//
//  Recorder.h
//  example
//
//  Created by dantheman on 1/20/15.
//
//

#pragma once
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "../DataTransform/Parser.h"
class Recorder{
public:
    Recorder();
    void setup(string path);
    void addMessage(ofxOscMessage &message);
    void save();
    bool isRecording();
    
private:
    ofxXmlSettings parse(ofxOscMessage message);
    string fileName;
    bool bRecording;
    float startTime;
    float endTime;
    int lastMessageNumber;
    ofxXmlSettings recording;
    Parser parser;
};