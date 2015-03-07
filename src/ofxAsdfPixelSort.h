#pragma once

#include "ofMain.h"

class ofxAsdfPixelSort {
public:
	void setup(ofImage&);
	void draw();
	
	void sortColumn();
	void sortRow();
	int getFirstNotBlackX(int _x, int _y);
	int getNextBlackX(int _x, int _y);
	int getFirstBrightX(int _x, int _y);
	int getNextDarkX(int _x, int _y);
	int getFirstNotWhiteX(int _x, int _y);
	int getNextWhiteX(int _x, int _y);
	int getFirstNotBlackY(int _x, int _y);
	int getNextBlackY(int _x, int _y);
	int getFirstBrightY(int _x, int _y);
	int getNextDarkY(int _x, int _y);
	int getFirstNotWhiteY(int _x, int _y);
	int getNextWhiteY(int _x, int _y);
	
private:
	template<typename T> inline int getPcolor(ofColor_<T> c) {
		return c.getHex() | 0xff000000;
	};
	ofImage img;
	
    int loops;
	int blackValue;
    int brigthnessValue;
    int whiteValue;
    
    int row;
    int column;
    
    bool saved;
	
    int mode;
	int width, height;
};
