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
    startTime = ofGetElapsedTimeMillis();
    //    recording.loadFile(fileName);
    recording.addTag("recording");
    recording.pushTag("recording");
    {
        recording.addValue("spec", "0.0.1");
        recording.addValue("kinectV2-OSC", "beta");
        recording.addValue("start-time", startTime);
        
    }recording.popTag();
    
    lastMessageNumber = 0;
}

//void Recorder::start(){
//    startThread(false);
//}
//
//void Recorder::stop(){
//    stopThread();
//}

//void Recorder::threadedFunction(){
//    while(isThreadRunning()){
//        if(lock()){
//            if(buffer.size() > 0){
//                int time = timeBuffer.front();
//                parser.setMessage(buffer.front());
//                if(parser.isBody() && !parser.isHand()) {
//                    ofxXmlSettings frame;
//                    
//                    int bodyCount = frame.addTag("body");
//                    frame.pushTag("body", bodyCount);
//                    {
//                        frame.addValue("id", parser.parseBodyId());
//                        frame.addValue("time", time);
//                        if(parser.isJoint()){
//                            int numJoint = frame.addTag("joint");
//                            frame.pushTag("joint", numJoint);
//                            {
//                                Joint j = parser.parseJoint();
//                                frame.addValue("type", j.getType());
//                                frame.addValue("tracked", j.getTrackingState()==0?"Tracked":"Inferred");
//                                frame.addValue("x", ofMap(j.getPoint().x, 0, ofGetWidth(), -1, 1, true));
//                                frame.addValue("y", ofMap(j.getPoint().y, ofGetHeight(), 0, -1, 1, true));
//                                frame.addValue("z", ofMap(j.getPoint().z, 30, 10, 0, 2, true));
//                            }
//                            frame.popTag();//joint
//                        }
//                    }frame.popTag();//body
//                    string file = parser.parseBodyId()+"-"+ofToString(time)+".xml";
//                    frame.save(file);
//                    recording.pushTag("recording");
//                    {
//                        lastMessageNumber = recording.addTag("file");
//                        recording.pushTag("file", lastMessageNumber);
//                        {
//                            recording.addValue("path", file);
//                            recording.addValue("time", time);
//                        }
//                        recording.popTag();
//                    }
//                    recording.popTag();
//                    
//                }
//                buffer.pop_front();
//                timeBuffer.pop_front();
//            }
//            unlock();
//        }
//    }
//}

void Recorder::addMessage(ofxOscMessage &message){
    int time = ofGetElapsedTimeMillis();
    parser.setMessage(message);
    if(parser.isBody() && !parser.isHand()) {
        ofxXmlSettings frame;
        
        int bodyCount = frame.addTag("body");
        frame.pushTag("body", bodyCount);
        {
            frame.addValue("id", parser.parseBodyId());
            frame.addValue("time", time);
            if(parser.isJoint()){
                int numJoint = frame.addTag("joint");
                frame.pushTag("joint", numJoint);
                {
                    Joint j = parser.parseJoint();
                    frame.addValue("type", j.getType());
                    frame.addValue("tracked", j.getTrackingState()==0?"Tracked":"Inferred");
                    frame.addValue("x", ofMap(j.getPoint().x, 0, ofGetWidth(), -1, 1, true));
                    frame.addValue("y", ofMap(j.getPoint().y, ofGetHeight(), 0, -1, 1, true));
                    frame.addValue("z", ofMap(j.getPoint().z, 30, 10, 0, 2, true));
                }
                frame.popTag();//joint
            }
        }frame.popTag();//body
        string file = parser.parseBodyId()+"-"+ofToString(time)+".xml";
        frame.save(file);
        recording.pushTag("recording");
        {
            lastMessageNumber = recording.addTag("file");
            recording.pushTag("file", lastMessageNumber);
            {
                recording.addValue("path", file);
                recording.addValue("time", time);
            }
            recording.popTag();
        }
        recording.popTag();
        
    }
}

void Recorder::save(){
    while(recording.getPushLevel() > 0){
        recording.popTag();
    }
    recording.pushTag("recording");
    {
        endTime = ofGetElapsedTimeMillis();
        recording.addValue("endTime", endTime);
        recording.addValue("duration", endTime - startTime);
    }
    recording.popTag();
    
    recording.save(fileName);
}

bool Recorder::isRecording(){
    return bRecording;
}