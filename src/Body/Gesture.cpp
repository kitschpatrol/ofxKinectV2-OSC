//
//  Gesture.cpp
//  skeletonReceiver
//
//  Created by dantheman on 1/29/15.
//
//

#include "Gesture.h"

Gesture::Gesture(){
    
}

Gesture::~Gesture(){
    
}

void Gesture::setup(string name, float threshold){
    this->name = name;
    triggerThresh = threshold;
}

void Gesture::setThreshold(float threshold){
    triggerThresh = threshold;
}

void Gesture::update(float value){
    if(value > triggerThresh){
        ofNotifyEvent(trigger, value, this);
    }
}