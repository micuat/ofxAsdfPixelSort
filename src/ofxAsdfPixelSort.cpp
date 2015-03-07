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
void ofxAsdfPixelSort::draw(){
    while (column < img.getWidth()-1) {
        sortColumn();
        column++;
        img.update();
    }
	while (row < img.getHeight()-1) {
        sortRow();
        row++;
		img.update();
		
    }
	
	img.draw(0,0);
	if(!saved && ofGetFrameNum() >= loops) {
		//ofSaveScreen(imgFileName+"_"+ofToString(mode)+".png");
		ofSaveFrame();
		saved = true;
		ofLogVerbose() << "DONE" << ofGetFrameNum();
	}
}

void ofxAsdfPixelSort::sortRow(){
    
    int x = 0;
    int y = row;
    int xend = 0;
    
    while (xend < img.getWidth()-1) {
        
        switch(mode) {
            case 0:
                x = getFirstNotBlackX(x, y);
                xend = getNextBlackX(x, y);
                break;
            case 1:
                x = getFirstBrightX(x, y);
                xend = getNextDarkX(x, y);
                break;
            case 2:
                x = getFirstNotWhiteX(x, y);
                xend = getNextWhiteX(x, y);
                break;
            default:
                break;
        }
        
        if (x < 0) break;
        
        int sortLength = xend-x;
		if(sortLength < 1) break;
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
				y = getFirstNotBlackY(x, y);
				yend = getNextBlackY(x, y);
				break;
			case 1:
				y = getFirstBrightY(x, y);
				yend = getNextDarkY(x, y);
				break;
			case 2:
				y = getFirstNotWhiteY(x, y);
				yend = getNextWhiteY(x, y);
				break;
			default:
				break;
		}
		
		if(y < 0) break;
		
		int sortLength = yend-y;
		if(sortLength < 1) break;
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
int ofxAsdfPixelSort::getFirstNotBlackX(int _x, int _y) {
	int x = _x;
	int y = _y;
	while(getPcolor(img.getColor(x,y)) < blackValue) {
		x++;
		if(x >= width) return -1;
	}
	return x;
}

int ofxAsdfPixelSort::getNextBlackX(int _x, int _y) {
	int x = _x+1;
	int y = _y;
	while(getPcolor(img.getColor(x,y)) > blackValue) {
		x++;
		if(x >= width) return width-1;
	}
	return x-1;
}

int ofxAsdfPixelSort::getFirstBrightX(int _x, int _y) {
	int x = _x;
	int y = _y;
	while(img.getColor(x,y).getBrightness() < brigthnessValue) {
		x++;
		if(x >= width) return -1;
	}
	return x;
}

int ofxAsdfPixelSort::getNextDarkX(int _x, int _y) {
	int x = _x+1;
	int y = _y;
	while(img.getColor(x,y).getBrightness() > brigthnessValue) {
		x++;
		if(x >= width) return width-1;
	}
	return x-1;
}

//WHITE
int ofxAsdfPixelSort::getFirstNotWhiteX(int _x, int _y) {
	int x = _x;
	int y = _y;
	while(getPcolor(img.getColor(x,y)) > whiteValue) {
		x++;
		if(x >= width) return -1;
	}
	return x;
}

int ofxAsdfPixelSort::getNextWhiteX(int _x, int _y) {
	int x = _x+1;
	int y = _y;
	while(getPcolor(img.getColor(x,y)) < whiteValue) {
		x++;
		if(x >= width) return width-1;
	}
	return x-1;
}


//BLACK
int ofxAsdfPixelSort::getFirstNotBlackY(int _x, int _y) {
	int x = _x;
	int y = _y;
	if(y < height) {
		while(getPcolor(img.getColor(x,y)) < blackValue) {
			y++;
			if(y >= height) return -1;
		}
	}
	return y;
}

int ofxAsdfPixelSort::getNextBlackY(int _x, int _y) {
	int x = _x;
	int y = _y+1;
	if(y < height) {
		while(getPcolor(img.getColor(x,y)) > blackValue) {
			y++;
			if(y >= height) return height-1;
		}
	}
	return y-1;
}

//BRIGHTNESS
int ofxAsdfPixelSort::getFirstBrightY(int _x, int _y) {
	int x = _x;
	int y = _y;
	if(y < height) {
		while(img.getColor(x,y).getBrightness() < brigthnessValue) {
			y++;
			if(y >= height) return -1;
		}
	}
	return y;
}

int ofxAsdfPixelSort::getNextDarkY(int _x, int _y) {
	int x = _x;
	int y = _y+1;
	if(y < height) {
		while(img.getColor(x,y).getBrightness() > brigthnessValue) {
			y++;
			if(y >= height) return height-1;
		}
	}
	return y-1;
}

//WHITE
int ofxAsdfPixelSort::getFirstNotWhiteY(int _x, int _y) {
	int x = _x;
	int y = _y;
	if(y < height) {
		while(getPcolor(img.getColor(x,y)) > whiteValue) {
			y++;
			if(y >= height) return -1;
		}
	}
	return y;
}

int ofxAsdfPixelSort::getNextWhiteY(int _x, int _y) {
	int x = _x;
	int y = _y+1;
	if(y < height) {
		while(getPcolor(img.getColor(x,y)) < whiteValue) {
			y++;
			if(y >= height) return height-1;
		}
	}
	return y-1;
}
