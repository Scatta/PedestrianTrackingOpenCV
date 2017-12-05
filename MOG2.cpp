#include "MOG2.h"
#include "stdafx.h"

MOG2::MOG2()
{
	pMOG2 = createBackgroundSubtractorMOG2(6, 16.0, false);
	/*
	int history				Length of the history.
	daouble varThreshold	Threshold on the squared Mahalanobis distance between the pixel and the model
							to decide whether a pixel is well described by the background model. 
							This parameter does not affect the background update.
	bool detectShadows		If true, the algorithm will detect shadows and mark them. 
							It decreases the speed a bit, so if you do not need this feature, 
							set the parameter to false.
	*/

}


MOG2::~MOG2()
{
}

void MOG2::ApplyFilter(Mat frame)
{
	pMOG2->apply(frame, im_fgMaskMOG2);
}