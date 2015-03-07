#pragma once

#include "ofMain.h"

class ofxAsdfPixelSort {
	enum Direction {
		X,
		Y
	};
	
public:
	void setup(ofImage&);
	void draw();
	
	void sortColumn();
	void sortRow();
	int getFirstNotBlack(Direction d, int _x, int _y);
	int getNextBlack(Direction d, int _x, int _y);
	int getFirstBright(Direction d, int _x, int _y);
	int getNextDark(Direction d, int _x, int _y);
	int getFirstNotWhite(Direction d, int _x, int _y);
	int getNextWhite(Direction d, int _x, int _y);
	
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
