#include "Mapper.h"

void Mapper::mapTo(vector<Skeleton>* skeletons) {
	this->skeletons = skeletons;
}

void Mapper::map(ofxOscMessage &_message) {
	parser.setMessage(_message);

	if(parser.isBody()) {
		Skeleton* skeleton = getSkeleton(parser.parseBodyId());

		if(parser.isJoint()) {
			skeleton->setJoint(parser.parseJoint());
		} else if(parser.isHand()) {
			skeleton->setHand(parser.parseHand());
        }else if(parser.isGesture()){
            Gesture foo;
            foo.type = parser.parseGestureType();
            foo.name = parser.parseGestureName();
            foo.value = parser.parseGestureValue();
            foo.triggered = parser.parseGestureTrigger();
            skeleton->gestures[foo.name] = foo;
            
            //ofLog()<<foo.name<<" "<<foo.value<<endl;

        }
    }
}

void Mapper::refresh() {
	skeletons->clear();
}

void Mapper::setSmoothing(SmoothingTechnique technique) {
	defaultSmoothing = technique;
}

Skeleton* Mapper::getSkeleton(string id) {
	for(int i = 0; i < skeletons->size(); i++) {
		if(skeletons->at(i).getBodyId() == id) {
			return &skeletons->at(i);
		}
	}
	return newSkeleton(id);
}

Skeleton* Mapper::newSkeleton(string id) {
	Skeleton skeleton;
	skeleton.init(id);
	skeleton.setSmoothing(defaultSmoothing);
	skeletons->push_back(skeleton);
	return &skeletons->at(skeletons->size()-1);
}