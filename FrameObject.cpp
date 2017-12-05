#include "stdafx.h"
#include "FrameObject.h"

int FrameObject::ObjectIDCntr = 0;

FrameObject::FrameObject(int lastseen, Point actMiddle)
{
	ObjectID = ObjectIDCntr;
	FrameObject::ObjectIDCntr++;
	LastSeenFrame = lastseen;
	MiddlePoint = actMiddle;
}


FrameObject::~FrameObject()
{
}
