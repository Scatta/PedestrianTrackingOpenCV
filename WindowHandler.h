#pragma once
#include "CompVision.h"
#include <string>
#include <iostream>

using namespace std;

class WindowHandler :
	public CompVision
{
public:
	static WindowHandler* GetInstance()
	{
		if (!instance)
		{
			instance = new WindowHandler();
		}
		return instance;
	}
	void KeyHandler(int key);
	void Help();
	void exportAndShowImage(string name, Mat &img, bool testMode);
	static int SearchArea;
	static int CompRate;
	static int ObjMin;
	static int ObjMax;
	static const string WindowName;
	static const string TrackbarWindowName;
	static const int FRAME_WIDTH;
	static const int FRAME_HEIGHT;
	static int PressedKey;
	static ostringstream testImageName;
	static int testImageCntr;
private:
	WindowHandler();
	static WindowHandler* instance;
};

