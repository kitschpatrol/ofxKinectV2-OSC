//
//  Player.cpp
//  example
//
//  Created by dantheman on 1/20/15.
//
//

#include "Player.h"
Player::Player(){
    
}
Player::~Player(){
    
}
void Player::setup(string path){
    if(ofFile::doesFileExist(ofToDataPath(path))){
        bool loaded = file.load(ofToDataPath(path));
        if(loaded){
            bPlay = true;
            startTime = ofGetElapsedTimeMillis();
            file.pushTag("recording");
            numTags = file.getNumTags("file");
            ofLog()<<"Captured :"<<numTags<<" number of bodies"<<endl;
            duration = file.getValue("duration", 0);
            ofLog()<<"total time "<<duration<<endl;
            for(int i = 0; i < numTags; i++){
                unsigned long long fooTime = file.getValue("file:time", 0, i);
                timeCodedPaths[fooTime] = file.getValue("file:path", "", i);
            }
            file.popTag();
            startTag = 0;
            endTag = numTags;
            
            sender.setup("127.0.0.1", 12345);
            start();
        }
    }
}
void Player::start(){
    startThread();
}

void Player::stop(){
    stopThread();
}

void Player::threadedFunction(){
    while(isThreadRunning()){
        if(lock()){
            previousTime = currentTime;
            currentTime = ofGetElapsedTimeMillis()%duration;
            if(currentTime < previousTime){
                startTag = 0;
            }
            bool fooBar = false;
            for(map<unsigned long long, string >::iterator iter = timeCodedPaths.begin(); iter != timeCodedPaths.end(); ++iter){
                if(iter->first >= previousTime && iter->first <= currentTime){
                    ofxXmlSettings currentMessage;
                    currentMessage.load(ofToDataPath(iter->second));
                    string id = currentMessage.getValue("body:id", "");
                    float x = currentMessage.getValue("body:joint:x", 0.0);
                    float y  = currentMessage.getValue("body:joint:y", 0.0);
                    float z = currentMessage.getValue("body:joint:z", 0.0);
                    string type = currentMessage.getValue("body:joint:type", "");
                    string tracked = currentMessage.getValue("body:joint:tracked", "");
                    ofxOscMessage b;
                    b.setAddress("/bodies/"+id+"/joints/"+type+"/");
                    b.addFloatArg(x);
                    b.addFloatArg(y);
                    b.addFloatArg(z);
                    b.addStringArg(tracked);
                    sender.sendMessage(b);
                }else if(iter->first > currentTime){
                    break;
                }
            }
            unlock();
        }
    }
}

