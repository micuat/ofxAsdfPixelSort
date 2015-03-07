#include "ofxAsdfPixelSort.h"

void ofxAsdfPixelSort::setup(ofImage& _img){
	img = _img;
	
	width = img.getWidth();
	height = img.getHeight();
	mode = 1;
	blackValue = -16000000;
	brigthnessValue = 60;
	whiteValue = -13000000;
	loops  = 1;
	row = 0;
	column = 0;
	saved = false;
}

//--------------------------------------------------------------
void ofxAsdfPixelSort::update(){
    if (column < img.getWidth()-1) {
        sortColumn();
        column++;
    }
	else if (row < img.getHeight()-1) {
        sortRow();
        row++;
    }
	img.update();
	
//	if(!saved && ofGetFrameNum() >= loops) {
//		//ofSaveScreen(imgFileName+"_"+ofToString(mode)+".png");
//		img.saveImage(ofToDataPath("mod.png"));
//		saved = true;
//		ofLogVerbose() << "DONE" << ofGetFrameNum();
//	}
}

//--------------------------------------------------------------
void ofxAsdfPixelSort::draw(){
	img.draw(0,0);
}

void ofxAsdfPixelSort::sortRow(){
    
    int x = 0;
    int y = row;
    int xend = 0;
    
    while (xend < img.getWidth()-1) {
        
        switch(mode) {
            case 0:
                x = getFirstNotBlack(X, x, y);
                xend = getNextBlack(X, x, y);
                break;
            case 1:
                x = getFirstBright(X, x, y);
                xend = getNextDark(X, x, y);
                break;
            case 2:
                x = getFirstNotWhite(X, x, y);
                xend = getNextWhite(X, x, y);
                break;
            default:
                break;
        }
        
        if (x < 0) break;
        
        int sortLength = xend-x;
		if(sortLength < 0) break;
		vector<int> unsorted(sortLength);
		vector<int> sorted(sortLength);
		
        for (int i=0; i<sortLength; i++) {
			unsorted[i] = img.getColor(x+i, y).getHex();
        }
        
        ofSort<int>(unsorted);
        
        for (int i=0; i<sortLength; i++) {
			ofColor c;
			c.setHex(unsorted[i]);
            img.setColor(x+i, y, c);
        }
        
        x = xend+1;
    }
}

void ofxAsdfPixelSort::sortColumn() {
	int x = column;
	int y = 0;
	int yend = 0;
	
	while(yend < img.getHeight()-1) {
		switch(mode) {
			case 0:
				y = getFirstNotBlack(Y, x, y);
				yend = getNextBlack(Y, x, y);
				break;
			case 1:
				y = getFirstBright(Y, x, y);
				yend = getNextDark(Y, x, y);
				break;
			case 2:
				y = getFirstNotWhite(Y, x, y);
				yend = getNextWhite(Y, x, y);
				break;
			default:
				break;
		}
		
		if(y < 0) break;
		
		int sortLength = yend-y;
		if(sortLength < 0) break;
		vector<int> unsorted(sortLength);
		
		for (int i=0; i<sortLength; i++) {
			unsorted[i] = img.getColor(x, y+i).getHex();
		}
		
		ofSort<int>(unsorted);
		
		for (int i=0; i<sortLength; i++) {
			ofColor c;
			c.setHex(unsorted[i]);
			img.setColor(x, y+i, c);
		}
		
		y = yend+1;
	}
}

//BLACK
int ofxAsdfPixelSort::getFirstNotBlack(Direction d, int _x, int _y) {
	int x = _x;
	int y = _y;
	
	if(x >= width) return -1;
	if(y >= height) return -1;
	
	while(getPcolor(img.getColor(x,y)) < blackValue) {
		if(d == X) x++;
		else y++;
		if(x >= width) return -1;
		if(y >= height) return -1;
	}
	
	if(d == X) return x;
	else return y;
}

int ofxAsdfPixelSort::getNextBlack(Direction d, int _x, int _y) {
	int x = _x;
	int y = _y;
	
	if(d == X) x++;
	else y++;
	
	if(x >= width) return width-1;
	if(y >= height) return height-1;
	
	while(getPcolor(img.getColor(x,y)) > blackValue) {
		if(d == X) x++;
		else y++;
		if(x >= width) return width-1;
		if(y >= height) return height-1;
	}
	
	if(d == X) return x-1;
	else return y-1;
}

int ofxAsdfPixelSort::getFirstBright(Direction d, int _x, int _y) {
	int x = _x;
	int y = _y;
	
	if(x >= width) return -1;
	if(y >= height) return -1;
	
	while(img.getColor(x,y).getBrightness() < brigthnessValue) {
		if(d == X) x++;
		else y++;
		if(x >= width) return -1;
		if(y >= height) return -1;
	}
	
	if(d == X) return x;
	else return y;
}

int ofxAsdfPixelSort::getNextDark(Direction d, int _x, int _y) {
	int x = _x;
	int y = _y;
	
	if(d == X) x++;
	else y++;
	
	if(x >= width) return width-1;
	if(y >= height) return height-1;
	
	while(img.getColor(x,y).getBrightness() > brigthnessValue) {
		if(d == X) x++;
		else y++;
		if(x >= width) return width-1;
		if(y >= height) return height-1;
	}
	
	if(d == X) return x-1;
	else return y-1;
}

//WHITE
int ofxAsdfPixelSort::getFirstNotWhite(Direction d, int _x, int _y) {
	int x = _x;
	int y = _y;
	
	if(x >= width) return -1;
	if(y >= height) return -1;
	
	while(getPcolor(img.getColor(x,y)) > whiteValue) {
		if(d == X) x++;
		else y++;
		if(x >= width) return -1;
		if(y >= height) return -1;
	}
	
	if(d == X) return x;
	else return y;
}

int ofxAsdfPixelSort::getNextWhite(Direction d, int _x, int _y) {
	int x = _x;
	int y = _y;
	
	if(d == X) x++;
	else y++;
	
	if(x >= width) return width-1;
	if(y >= height) return height-1;
	
	while(getPcolor(img.getColor(x,y)) < whiteValue) {
		if(d == X) x++;
		else y++;
		if(x >= width) return width-1;
		if(y >= height) return height-1;
	}
	
	if(d == X) return x-1;
	else return y-1;
}
