//
//  Recorder.cpp
//  example
//
//  Created by dantheman on 1/20/15.
//
//

#include "Recorder.h"
Recorder::Recorder(){
    
}

void Recorder::setup(string path){
    fileName = path+ofGetTimestampString();
    if(!ofIsStringInString(fileName, ".xml")){
        fileName+=".xml";
    }
    
    //    recording.loadFile(fileName);
    recording.addTag("recording");
    recording.pushTag("recording");
    {
        recording.addValue("spec", "0.0-beta");
        recording.addTag("kinectV2");
        recording.pushTag("kinectV2");
        {
            recording.addTag("header");
            recording.pushTag("header");//<headers>
            {
                recording.addTag("client");//<client>
                recording.pushTag("client");
                {
                    recording.addValue("name", "KinectV2-OSC");
                    recording.addValue("version", 1.0);
                    recording.addValue("username", "beta-user");
                }
                recording.popTag();//</client>
                
                
                
                recording.addTag("offset");
                recording.pushTag("offset");//<offset>
                {
                    recording.addValue("x", 0);
                    recording.addValue("y", 0);
                    recording.addValue("z", 0);
                }
                recording.popTag();//</offset>
                
                recording.addTag("up");
                recording.pushTag("up");//<up>
                {
                    recording.addValue("x", 0);
                    recording.addValue("y", -1);
                    recording.addValue("z", 0);
                }
                recording.popTag();//</up>
                
                recording.addTag("screenBounds");
                recording.pushTag("screenBounds");//<screenBounds>
                {
                    recording.addValue("x", ofGetWidth());
                    recording.addValue("y", ofGetHeight());
                    recording.addValue("z", 0);
                }
                recording.popTag();//</screenBounds>
            }recording.popTag();//</header>
        }recording.popTag();
    }recording.popTag();
    
    lastMessageNumber = 0;
    startTime = ofGetElapsedTimef();
    recording.saveFile(fileName);
}
void Recorder::addMessage(ofxOscMessage &message){
    //if(bRecording){
    float time = ofGetElapsedTimef();
    parser.setMessage(message);
    if(parser.isBody() && !parser.isHand()) {
        recording.pushTag("recording");
        {
            int bodyCount = recording.addTag("body");
            recording.pushTag("body", bodyCount);
            {
                recording.addValue("id", parser.parseBodyId());
                recording.addValue("time", time-startTime);
                if(parser.isJoint()){
                    int numJoint = recording.addTag("joint");
                    recording.pushTag("joint", numJoint);
                    {
                        Joint j = parser.parseJoint();
                        recording.addValue("type", j.getType());
                        recording.addValue("x", j.getPoint().x);
                        recording.addValue("y", j.getPoint().y);
                        recording.addValue("z", j.getPoint().z);
                    }
                    recording.popTag();//joint
                }
//                if(parser.isHand()){
//                    int handCount = recording.addTag("hand");
//                    recording.pushTag("hand", handCount);
//                    {
//                        Hand h = parser.parseHand();
//                        
//                        recording.addValue("confidence", h.getConfidence()==HIGH?1:0);
//                        recording.addValue("position", h.getPosition()==LEFT?"left":"right");
//                        recording.addValue("state", h.getState()==OPEN?"open":"closed");
//                        
//                    }
//                    recording.popTag();//hand
//                }
            }recording.popTag();//body
        }recording.popTag();//recording
    }
    //    save();
    //}
}

void Recorder::save(){
    while(recording.getPushLevel() > 0){
        recording.popTag();
    }
    recording.save(fileName);
}

bool Recorder::isRecording(){
    return bRecording;
}