#pragma once
#include "CompVision.h"

class FrameObject :
	public CompVision
{
public:
	FrameObject(int lastseen, Point actMiddle);
	~FrameObject();
	int ObjectID;
	int LastSeenFrame;
	Point MiddlePoint;
	static int ObjectIDCntr;
};

