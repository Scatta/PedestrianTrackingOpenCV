#pragma once
#include "CompVision.h"
#include "FrameHandler.h"

class Contouring :
	public CompVision
{
public:
	Contouring();
	~Contouring();
	void GetImgContours(FrameHandler& frames, Mat &threshedimg, Mat &original);
	Mat im_Contours;
};

