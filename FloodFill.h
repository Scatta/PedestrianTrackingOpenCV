#pragma once

#include "CompVision.h"

class FloodFill :
	public CompVision
{
public:
	FloodFill();
	~FloodFill();
	void ApplyFloodfill(FloodFill& floodfill, Mat& fgMaskMOG2clone, Mat& im_mog2);
	Mat im_FloodFill;
private:
	void MorphIt(Mat &img);
	static int ErodeFact;
	static int DilateFact;

};

