#include "FloodFill.h"
#include "stdafx.h"

int FloodFill::ErodeFact = 2;
int FloodFill::DilateFact = 2;

FloodFill::FloodFill()
{
}


FloodFill::~FloodFill()
{
}


void FloodFill::ApplyFloodfill(FloodFill& floodfill, Mat& fgMaskMOG2clone, Mat& im_mog2)
{
	Mat im_original = fgMaskMOG2clone;
	floodFill(im_original, Point(0, 0), Scalar(255));
	Mat im_floodfill_inv;
	bitwise_not(im_original, im_floodfill_inv);
	floodfill.im_FloodFill = (im_mog2 | im_floodfill_inv);
	MorphIt(floodfill.im_FloodFill);
}

void FloodFill::MorphIt(Mat &img)
{
	erode(img, img, getStructuringElement(MORPH_RECT, Size(ErodeFact, ErodeFact)));
	dilate(img, img, getStructuringElement(MORPH_RECT, Size(DilateFact, DilateFact)));
}