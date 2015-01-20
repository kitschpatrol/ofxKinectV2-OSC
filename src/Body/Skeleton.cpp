#include "Skeleton.h"

void Skeleton::init(string _bodyId) {
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
        leftHand.clone(&hand);
	} else {
        rightHand.clone(&hand);
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
    resetFreshness();
    
//	if (jointType == "ThumbRight") {
//		setThumbRight(joint);
//	} else if (jointType == "SpineBase") {
//		setSpineBase(joint);
//	} else if (jointType == "SpineMid") {
//		setSpineMid(joint);
//	} else if (jointType == "Neck") {
//		setNeck(joint);
//	} else if (jointType == "Head") {
//		setHead(joint);
//	} else if (jointType == "ShoulderLeft") {
//		setShoulderLeft(joint);
//	} else if (jointType == "ElbowLeft") {
//		setElbowLeft(joint);
//	} else if (jointType == "WristLeft") {
//		setWristLeft(joint);
//	} else if (jointType == "HandLeft") {
//		setHandLeft(joint);
//	} else if (jointType == "ShoulderRight") {
//		setShoulderRight(joint);
//	} else if (jointType == "ElbowRight") {
//		setElbowRight(joint);
//	} else if (jointType == "WristRight") {
//		setWristRight(joint);
//	} else if (jointType == "HandRight") {
//		setHandRight(joint);
//	} else if (jointType == "HipLeft") {
//		setHipLeft(joint);
//	} else if (jointType == "KneeLeft") {
//		setKneeLeft(joint);
//	} else if (jointType == "AnkleLeft") {
//		setAnkleLeft(joint);
//	} else if (jointType == "FootLeft") {
//		setFootLeft(joint);
//	} else if (jointType == "HipRight") {
//		setHipRight(joint);
//	} else if (jointType == "KneeRight") {
//		setKneeRight(joint);
//	} else if (jointType == "AnkleRight") {
//		setAnkleRight(joint);
//	} else if (jointType == "FootRight") {
//		setFootRight(joint);
//	} else if (jointType == "SpineShoulder") {
//		setSpineShoulder(joint);
//	} else if (jointType == "HandTipLeft") {
//		setHandTipLeft(joint);
//	} else if (jointType == "ThumbLeft") {
//		setThumbLeft(joint);
//	} else if (jointType == "HandTipRight") {
//		setHandTipRight(joint);
//	}
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
    leftHand.clone(&hand);
    resetFreshness();
}

void Skeleton::setRightHand(Hand &hand) {
    rightHand.clone(&hand);
    resetFreshness();
}

void Skeleton::setThumbRight(Joint &joint) {
    thumbRight.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setSpineBase(Joint &joint) {
    spineBase.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setSpineMid(Joint &joint) {
    spineMid.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setNeck(Joint &joint) {
    neck.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHead(Joint &joint) {
    head.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setShoulderLeft(Joint &joint) {
    shoulderLeft.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setElbowLeft(Joint &joint) {
    elbowLeft.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setWristLeft(Joint &joint) {
    wristLeft.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHandLeft(Joint &joint) {
    handLeft.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setShoulderRight(Joint &joint) {
    shoulderRight.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setElbowRight(Joint &joint) {
    elbowRight.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setWristRight(Joint &joint) {
    wristRight.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHandRight(Joint &joint) {
    handRight.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHipLeft(Joint &joint) {
    hipLeft.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setKneeLeft(Joint &joint) {
    kneeLeft.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setAnkleLeft(Joint &joint) {
    ankleLeft.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setFootLeft(Joint &joint) {
    footLeft.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHipRight(Joint &joint) {
    hipRight.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setKneeRight(Joint &joint) {
    kneeRight.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setAnkleRight(Joint &joint) {
    ankleRight.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setFootRight(Joint &joint) {
    footRight.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setSpineShoulder(Joint &joint) {
    spineShoulder.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHandTipLeft(Joint &joint) {
    handTipLeft.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setThumbLeft(Joint &joint) {
    thumbLeft.clone(&joint, smoothing);
    resetFreshness();
}

void Skeleton::setHandTipRight(Joint &joint) {
    handTipRight.clone(&joint, smoothing);
    resetFreshness();
}