#pragma once
#include "CompVision.h"
#include "WindowHandler.h"
#include "Frame.h"
#include "FrameObject.h"

class FrameHandler :
	public CompVision
{
public:
	FrameHandler();
	~FrameHandler();
	void processingFrames(FrameHandler& frames, Mat original);

	Mat im_Final;
	static int frameCntr;
	vector<Frame*> frameVector;

private:
	double getCorrelation(Mat src_base, Mat src_test);
	void increaseFrameCntr();
	int returnPrevCntr(int val);
	int getFrameObjectID(FrameHandler& frames, Point middlePoint);
	void deleteGhostObjects(FrameHandler& frames);

	static const int frameHistorySize;
	vector<FrameObject*> frameObjectVector;

};

