#include "Skeleton.h"
void Skeleton::init(string _bodyId, bool recording) {
    bodyId = _bodyId;
    setupMap();
    resetFreshness();
}
void Skeleton::setupMap(){
    string jointArray[] = {
        "SpineBase",
        "SpineMid",
        "Neck",
        "Head",
        "ShoulderLeft",
        "ElbowLeft",
        "WristLeft",
        "HandLeft",
        "ShoulderRight",
        "ElbowRight",
        "WristRight",
        "HandRight",
        "HipLeft",
        "KneeLeft",
        "AnkleLeft"	,
        "FootLeft"	,
        "HipRight"	,
        "KneeRight"	,
        "AnkleRight"	,
        "FootRight"	,
        "SpineShoulder",
        "HandTipLeft"	,
        "ThumbLeft"	,
        "HandTipRight",
        "ThumbRight"	,
    };
    for(int i = 0 ; i < 25; i++){
        joints[jointArray[i]] = new Joint();
    }
    hands["Left"] = new Hand();
    hands["Right"] = new Hand();
}

void Skeleton::setSmoothing(SmoothingTechnique technique) {
    smoothing = technique;
}

void Skeleton::update() {
    freshness--;
}

void Skeleton::resetFreshness() {
    freshness = MAX_FRESHNESS;
}

bool Skeleton::isStale() {
    return freshness == 0;
}

bool Skeleton::isCloserThan(Skeleton* other) {
    return spineShoulder.z() > other->getSpineShoulder().z();
}

void Skeleton::setHand(Hand hand) {
    string index = "";
    if(hand.isLeft()) {
        hands["Left"]->clone(&hand);
    } else {
        hands["Right"]->clone(&hand);
    }
}

void Skeleton::transform(ofMatrix4x4 mat){
    for(map<string, Joint*>::iterator iter = joints.begin(); iter != joints.end(); ++iter){
        ofVec3f pt = iter->second->getPoint();
        iter->second->setPoint(pt*mat);
    }
}


void Skeleton::setJoint(Joint joint) {
    string jointType = joint.getType();
    
    joints[jointType]->clone(&joint);

//    pts[jointType] = joints[jointType]->getPoint();
    
//    if(recording){
//        if (jointType == "ThumbRight") {
//            saveSk.ThumbRight = joints[jointType]->getPoint();
//        } else if (jointType == "SpineBase") {
//            saveSk.SpineBase = joints[jointType]->getPoint();
//        } else if (jointType == "SpineMid") {
//            saveSk.SpineMid = joints[jointType]->getPoint();
//        } else if (jointType == "Neck") {
//            saveSk.Neck = joints[jointType]->getPoint();
//        } else if (jointType == "Head") {
//            saveSk.Head = joints[jointType]->getPoint();
//        } else if (jointType == "ShoulderLeft") {
//            saveSk.ShoulderLeft = joints[jointType]->getPoint();
//        } else if (jointType == "ElbowLeft") {
//            saveSk.ElbowLeft = joints[jointType]->getPoint();
//        } else if (jointType == "WristLeft") {
//            saveSk.WristLeft = joints[jointType]->getPoint();
//        } else if (jointType == "HandLeft") {
//            saveSk.HandLeft = joints[jointType]->getPoint();
//        } else if (jointType == "ShoulderRight") {
//            saveSk.ShoulderRight = joints[jointType]->getPoint();
//        } else if (jointType == "ElbowRight") {
//            saveSk.ElbowRight = joints[jointType]->getPoint();
//        } else if (jointType == "WristRight") {
//            saveSk.WristRight = joints[jointType]->getPoint();
//        } else if (jointType == "HandRight") {
//            saveSk.HandRight = joints[jointType]->getPoint();
//        } else if (jointType == "HipLeft") {
//            saveSk.HipLeft = joints[jointType]->getPoint();
//        } else if (jointType == "KneeLeft") {
//            saveSk.KneeLeft = joints[jointType]->getPoint();
//        } else if (jointType == "AnkleLeft") {
//            saveSk.AnkleLeft = joints[jointType]->getPoint();
//        } else if (jointType == "FootLeft") {
//            saveSk.FootLeft = joints[jointType]->getPoint();
//        } else if (jointType == "HipRight") {
//            saveSk.HipRight = joints[jointType]->getPoint();
//        } else if (jointType == "KneeRight") {
//            saveSk.KneeRight = joints[jointType]->getPoint();
//        } else if (jointType == "AnkleRight") {
//            saveSk.AnkleRight = joints[jointType]->getPoint();
//        } else if (jointType == "FootRight") {
//            saveSk.FootRight = joints[jointType]->getPoint();
//        } else if (jointType == "SpineShoulder") {
//            saveSk.SpineShoulder = joints[jointType]->getPoint();
//        } else if (jointType == "HandTipLeft") {
//            saveSk.HandTipLeft = joints[jointType]->getPoint();
//        } else if (jointType == "ThumbLeft") {
//            saveSk.ThumbLeft = joints[jointType]->getPoint();
//        } else if (jointType == "HandTipRight") {
//            saveSk.HandTipRight = joints[jointType]->getPoint();
//        }
//    }
    
    resetFreshness();
}

Hand Skeleton::getLeftHand() {
    return *hands["Left"];
}

Hand Skeleton::getRightHand() {
    return *hands["Right"];
}

string Skeleton::getBodyId() {
    return bodyId;
}

Joint Skeleton::getThumbRight() {
    return *joints["ThumbRight"];
}

Joint Skeleton::getSpineBase() {
    return *joints["SpineBase"];
}

Joint Skeleton::getSpineMid() {
    return *joints["SpineMid"];
}

Joint Skeleton::getNeck() {
    return *joints["Neck"];
}

Joint Skeleton::getHead() {
    return *joints["Head"];
}

Joint Skeleton::getShoulderLeft() {
    return *joints["ShoulderLeft"];
}

Joint Skeleton::getElbowLeft() {
    return *joints["ElbowLeft"];
}

Joint Skeleton::getWristLeft() {
    return *joints["WristLeft"];
}

Joint Skeleton::getHandLeft() {
    return *joints["HandLeft"];
}

Joint Skeleton::getShoulderRight() {
    return *joints["ShoulderRight"];;
}

Joint Skeleton::getElbowRight() {
    return *joints["ElbowRight"];
}

Joint Skeleton::getWristRight() {
    return *joints["WristRight"];
}

Joint Skeleton::getHandRight() {
    return *joints["HandRight"];
}

Joint Skeleton::getHipLeft() {
    return *joints["HipLeft"];
}

Joint Skeleton::getKneeLeft() {
    return *joints["KneeLeft"];
}

Joint Skeleton::getAnkleLeft() {
    return *joints["AnkleLeft"];
}

Joint Skeleton::getFootLeft() {
    return *joints["FootLeft"];
}

Joint Skeleton::getHipRight() {
    return *joints["HipRight"];
}

Joint Skeleton::getKneeRight() {
    return *joints["KneeRight"];
}

Joint Skeleton::getAnkleRight() {
    return *joints["AnkleRight"];
}

Joint Skeleton::getFootRight() {
    return *joints["FootRight"];
}

Joint Skeleton::getSpineShoulder() {
    return *joints["SpineShoulder"];
}

Joint Skeleton::getHandTipLeft() {
    return *joints["HandTipLeft"];
}

Joint Skeleton::getThumbLeft() {
    return *joints["ThumbLeft"];
}

Joint Skeleton::getHandTipRight() {
    return *joints["HandTipRight"];
}

ofRectangle Skeleton::getLeftHandRange() {
    return interpreter.leftHandRange(joints["SpineSholder"], joints["ShoulderLeft"]);
}

ofRectangle Skeleton::getRightHandRange() {
    return interpreter.leftHandRange(joints["SpineSholder"], joints["ShoulderRight"]);
}

ofVec2f Skeleton::getLeftHandNormal() {
    return interpreter.leftHandNormal(joints["HandLeft"], joints["SpineSholder"], joints["ShoulderLeft"]);
}

ofVec2f Skeleton::getRightHandNormal() {
    return interpreter.rightHandNormal(joints["HandRight"], joints["SpineSholder"], joints["ShoulderRight"]);
    
}

//void Skeleton::setJoint(Joint &joint){
//    joints[joint.getType()].clone(joint);
//}


void Skeleton::setLeftHand(Hand &hand) {
    hands["Left"]->clone(&hand);
    
    resetFreshness();
}

void Skeleton::setRightHand(Hand &hand) {
    hands["Right"]->clone(&hand);
    
    resetFreshness();
}

void Skeleton::setThumbRight(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    
    resetFreshness();
}

void Skeleton::setSpineBase(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    //    spineBase.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setSpineMid(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    
    resetFreshness();
}

void Skeleton::setNeck(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    
    resetFreshness();
}

void Skeleton::setHead(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    
    resetFreshness();
}

void Skeleton::setShoulderLeft(Joint &joint) {
    shoulderLeft.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setElbowLeft(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    
    resetFreshness();
}

void Skeleton::setWristLeft(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    
    resetFreshness();
}

void Skeleton::setHandLeft(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    
    resetFreshness();
}

void Skeleton::setShoulderRight(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    
    resetFreshness();
}

void Skeleton::setElbowRight(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    
    resetFreshness();
}

void Skeleton::setWristRight(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHandRight(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHipLeft(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setKneeLeft(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setAnkleLeft(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setFootLeft(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHipRight(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setKneeRight(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setAnkleRight(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setFootRight(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setSpineShoulder(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHandTipLeft(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setThumbLeft(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHandTipRight(Joint &joint) {
    joints[joint.getType()]->clone(&joint, smoothing);
    resetFreshness();
}