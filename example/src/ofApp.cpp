#include "ofApp.h"

int whiteKeys[12]= {0,2,4,5,7,9,11,12,14,16,17,19};


bool ofApp::bPointInsideBox(ofPoint startPos, ofPoint endPos, ofPoint pt){
    
    
    bool bIn = false;
    if (( pt.x >= startPos.x ) && ( pt.x <= endPos.x ) &&
        ( pt.y >= startPos.y ) && ( pt.y <= endPos.y ) &&
        ( pt.z >= startPos.z ) && ( pt.z <= endPos.z ) ){
        
        bIn = true;
    }
    
    return bIn;
    
}

void ofApp::setup(){
	
    
    ser.listDevices();
    ser.setup(0, 115200);
    
    
    smallFont.loadFont("selena.otf", 16); //http://openfontlibrary.org/en/font/selena
	largeFont.loadFont("selena.otf", 48);

	ofSetLineWidth(8);
	ofSetFrameRate(60);
	kinect.setup(12345, smallFont);
	kinect.setSmoothing(SIMPLE_MOVING_AVERAGE);
    skeletons = kinect.getSkeletons();
	renderer.setup(skeletons, largeFont);
    
    
    gui.setup("panel");
    gui.add(boxDim.set("box dimensions", ofPoint(0,0,0), ofPoint(0,0,0), ofPoint(400,400,400)));
    gui.add(boxPosStart.set("box pos start", ofPoint(0,0,0), ofPoint(-500,-500,-1500), ofPoint(500,500,1500)));
    gui.add(boxPosEnd.set("box pos end", ofPoint(0,0,0), ofPoint(-500,-500,-1500), ofPoint(500,500,1500)));
    gui.add(nDivisions.set("nDivisions", 12, 0, 20));
    
    
    gui.add(scale.set("scale", ofPoint(1,1,1), ofPoint(0.01,0.01,0.01), ofPoint(40,40,40)));
    gui.add(offset.set("offset", ofPoint(0,0,0), ofPoint(-1000,-1000,-1000), ofPoint(1000,1000,1000)));
    gui.add(rotationX.set("rotationX", 0,-180,180));
    gui.add(rotationY.set("rotationY", 0,-180,180));
    gui.add(rotationZ.set("rotationZ", 0,-180,180));
    


    
    
    
    
    
    gui.loadFromFile("settings.xml");
    
    
    bInside.clear();
    bInside.assign(nDivisions, false);
    
    
    
    midi.listPorts();
    midi.openPort(0);

    
    
}

void ofApp::update(){
	
    
    if (bInside.size() != nDivisions){
        bInside.clear();
        bInside.assign(nDivisions, false);
    }
    
    
    //Each frame check for new Kinect OSC messages
	kinect.update();
    
    if (ofGetFrameNum() < 10){
        cam.setPosition(698.314, 1647.53, -28.9273);
        cam.setOrientation(ofPoint(-112.963, -90.1957, 1.08879));
    }
}


void ofApp::draw(){

    ofEnableDepthTest();
    
	ofBackground(ofColor::darkGray);
    
    
    
    cam.begin();
    ofMatrix4x4 mat;
    ofPoint offsetPt = offset;
    mat.glTranslate(offsetPt);
    mat.glRotate(rotationX, 1,0,0);
    mat.glRotate(rotationY, 0,1,0);
    mat.glRotate(rotationZ, 0,0,1);
    ofPoint scaleTemp = scale;
    mat.glScale(scaleTemp.x, scaleTemp.y, scaleTemp.z);
    ofPushMatrix();
    ofMultMatrix(mat);
    renderer.draw();
    ofPopMatrix();
    
    //------------------------- draw stuff
    ofDrawGridPlane(1000);
    ofDrawAxis(50);
    
    for (int i = 0; i < nDivisions; i++){
        
        
        
        ofPoint end = boxPosEnd;
        ofPoint start = boxPosStart;
        ofPoint dim = boxDim;
        ofPoint diff = end - start;
        
        ofBoxPrimitive prim;
        prim.set(dim.x, dim.y, dim.z);
        
        prim.setPosition(start + (diff/nDivisions) * i);
       
        bool bPrevOn = bInside[i];
        
        bInside[i] = false;
        
        
        for(int j = 0; j < skeletons->size(); j++) {
            ofPoint left = skeletons->at(j).getAnkleLeft().getPoint();
            ofPoint right = skeletons->at(j).getAnkleRight().getPoint();
            left = left * mat;
            right = right * mat;
            
            ofPoint midPt = start + (diff/nDivisions) * i;
            ofPoint start = midPt - dim/2;
            ofPoint end = midPt + dim/2;
            
            
            bool bIn = bPointInsideBox(start, end, left) | bPointInsideBox(start, end, right);
            if (bIn == true) bInside[i] = true;
        }
        
        if (bInside[i] == true){
            ser.writeByte(11-i);
        }
        
        if (bPrevOn != bInside[i] && bInside[i] == true){
            int note = 48 + whiteKeys[i];
            int velocity = 100; //results[i].startVelocity;
            midi.sendNoteOn(1, note,  velocity);
            
            
            
        } else if (bPrevOn != bInside[i] && bInside[i] == false){
            int note = 48 + whiteKeys[i];
            int velocity = 100; //results[i].startVelocity;
            midi.sendNoteOff(1, note,  velocity);
        }
        
        
        
        
        ofPushMatrix();
        if (bInside[i] == true) ofSetColor(ofColor::cyan);
        else ofSetColor(ofColor::white);
            prim.draw();
        ofPopMatrix();
        
    }
    
    //------------------------- sekeltons
   
    

    for(int i = 0; i < skeletons->size(); i++) {
        
        ofPoint left = skeletons->at(i).getAnkleLeft().getPoint();
        ofPoint right = skeletons->at(i).getAnkleRight().getPoint();
        
        
        left = left * mat;
        right = right * mat;
        
        
        
        
        
        
        ofSetColor(ofColor::pink);
        ofSpherePrimitive sphere;
        sphere.setRadius(30);
        
        
        ofPushMatrix();
        ofTranslate(left);
        sphere.getMesh().drawWireframe();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(right);
        sphere.getMesh().drawWireframe();
        ofPopMatrix();
    }
    
    
    
    cam.end();

    ofSetColor(ofColor::white);
    
    ofDisableDepthTest();
    gui.draw();
    
}

void ofApp::keyPressed(int key){

    
    if (key == 'c'){
        cam.setPosition(698.314, 1647.53, -28.9273);
        cam.setOrientation(ofPoint(-112.963, -90.1957, 1.08879));

    }
    
    if (key == 's'){
        gui.saveToFile("settings.xml");
    }
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
