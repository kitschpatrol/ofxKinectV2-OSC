//
//  Gesture.h
//  skeletonReceiver
//
//  Created by dantheman on 1/29/15.
//
//

#pragma once
#include "ofMain.h"
enum GestureType{
    Discrete = 0,
    Continuous
};

class Gesture{
public:
    void setup(string name, float value, bool triggered);
    string name;
    float value;
    bool triggered;
    GestureType type;
};