#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofImage img;
	img.loadImage(ofToDataPath("photo.jpg"));
	aps.setup(img);
	
	ofSetWindowShape(img.getWidth(), img.getHeight());
	
	saved = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	aps.update();
	
	if( aps.isSortDone() && !saved ) {
		aps.getImage().saveImage(ofToDataPath("sorted.jpg"));
		saved = true;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	aps.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
