#pragma once

#include "ofMain.h"

class ofxAsdfPixelSort {
	enum Direction {
		X,
		Y
	};
	
public:
	void setup(ofImage& _img,
			   int _mode = 1,
			   int _steps = 1,
			   int _blackValue = -16000000,
			   int _brightnessValue = 60,
			   int _whiteValue = -13000000);
	void update();
	void draw();
	
	void sortColumn();
	void sortRow();
	int getFirstNotBlack(Direction d, int _x, int _y);
	int getNextBlack(Direction d, int _x, int _y);
	int getFirstBright(Direction d, int _x, int _y);
	int getNextDark(Direction d, int _x, int _y);
	int getFirstNotWhite(Direction d, int _x, int _y);
	int getNextWhite(Direction d, int _x, int _y);
	
	bool isSortDone() { return sortDone; };
	ofImage getImage() { return img; };
	
private:
	template<typename T> inline int getPcolor(ofColor_<T> c) {
		return c.getHex() | 0xff000000;
	};
	
	ofImage img;
	
    int steps;
	int blackValue;
    int brigthnessValue;
    int whiteValue;
    
    int row;
    int column;
    
    bool sortDone;
	
    int mode;
	int width, height;
};
