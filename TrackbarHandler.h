#pragma once
#include "CompVision.h"

class TrackbarHandler :
	public CompVision
{
public:
	static TrackbarHandler* GetInstance()
	{
		if (!instance)
		{
			instance = new TrackbarHandler();
		}
		return instance;
	}
	void createTrackbars();
private:
	TrackbarHandler();
	static TrackbarHandler* instance;
};

