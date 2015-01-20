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
    ofRemoveListener(ofEvents().update, this, &Player::update);
}
void Player::setup(string path){
    ofLog()<<path<<endl;
    if(ofFile::doesFileExist(ofToDataPath(path))){
        bool loaded = file.load(ofToDataPath(path));
        if(loaded){
            bPlay = true;
            startTime = ofGetElapsedTimef();
            file.pushTag("recording");
            numTags = file.getNumTags("body");
            ofLog()<<"Captured :"<<numTags<<" number of bodies"<<endl;
            endTime = file.getValue("body:time", 0.0, numTags-1);
            ofLog()<<"total time "<<endTime<<endl;
            vector<string> ids;
            for(int i = 0; i < numTags; i++){
                if(find(ids.begin(), ids.end(),file.getValue("body:id", "", i))==ids.end()){
                    ids.push_back(file.getValue("body:id", "", i));
                    Skeleton & foo = bodies[ids.back()];
                    foo.init(ids.back());
                }
            }
            startTag = 0;
            endTag = numTags;
            ofAddListener(ofEvents().update, this, &Player::update);
        }
    }
}
void Player::update(ofEventArgs & args){
    if(bPlay){
        previousTime = currentTime;
        currentTime = fmodf(ofGetElapsedTimef(), endTime);
        if(currentTime < previousTime){
            startTag = 0;
        }
        for(int i = startTag; i < numTags; i++){
            float time = file.getValue("body:time", 0.0, i);
            if(time > previousTime && time <= currentTime){
                Joint j = Joint();
                j.setPoint(ofVec3f(file.getValue("body:joint:x", 0, i), file.getValue("body:joint:y", 0, i), file.getValue("body:joint:z", 0, i)));
                j.setType((file.getValue("body:joint:type", "", i)));
                bodies[file.getValue("body:id", "", i)].setJoint(j);
            }else if(time > currentTime){
                startTag = i;
                break;
            }
        }
    }
}
vector<Skeleton> Player::getSkeleton(){
    vector<Skeleton> data;
    for(map<string, Skeleton>::iterator iter = bodies.begin(); iter != bodies.end(); ++iter){
        data.push_back(iter->second);
    }
    return data;
}
void Player::draw(){
    ofDrawBitmapString("PLAYING BACK FROM FILE", ofGetWidth()-100, ofGetHeight()-100);
}