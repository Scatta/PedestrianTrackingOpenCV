#pragma once
#include "CompVision.h"
#include "WindowHandler.h"

class Frame :
	public CompVision
{
public:
	Frame();
	~Frame();
	vector<Mat> frameImages;
	vector<Rect> frameLocations;
};

