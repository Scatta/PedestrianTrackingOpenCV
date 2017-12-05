#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h> 
#include "WindowHandler.h"
#include "TrackbarHandler.h"
#include "MOG2.h"
#include "FloodFill.h"
#include "Contouring.h"
#include "FrameHandler.h"

Mat im_Frame;

bool videoMode = true;
string video_name = "Videos/BorarosA_Sun_ManyPed_1.mov";
double videoFPS = 0.0;
clock_t beginTime = clock();
clock_t endTime = clock();
double elapsedSecs = 0.0;
int frameDelay = 0;
int delayCntr = 0;
bool testMode = false;

int main()
{
	VideoCapture capture;
	VideoCapture cap;	
	TrackbarHandler::GetInstance()->createTrackbars();
	MOG2 mog2;
	FloodFill floodfill;
	Contouring contours;
	FrameHandler framehandler;

	WindowHandler::GetInstance()->Help();

	if (videoMode)
	{
		if (!capture.open(video_name))
			return 0;

		videoFPS = capture.get(CV_CAP_PROP_FPS);
	}
	else   // camera mode
	{
		if (!capture.open(0))
			return 0;
	}
	capture.set(CV_CAP_PROP_FRAME_WIDTH, WindowHandler::FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, WindowHandler::FRAME_HEIGHT);

	while (waitKey(30) != 27)  //wait for esc
	{
		beginTime = clock();

		delayCntr = 0;
		if (videoMode == true && elapsedSecs != 0.0 && videoFPS != 0.0)
		{   // video delay
			frameDelay = int(elapsedSecs * videoFPS) / 2;
			frameDelay = frameDelay * 2;
			while (delayCntr <= frameDelay)
			{
				capture.read(im_Frame);
				delayCntr++;
			}
		}
		else
		{
			capture.read(im_Frame);
		}

		if (im_Frame.empty()) break;

		if (testMode)
		{
			WindowHandler::GetInstance()->exportAndShowImage("Original", im_Frame, testMode);
		}

		mog2.ApplyFilter(im_Frame);
		if (testMode)
		{
			WindowHandler::GetInstance()->exportAndShowImage("FGMaskMOG2", mog2.im_fgMaskMOG2, testMode);
		}
		
		floodfill.ApplyFloodfill(floodfill, mog2.im_fgMaskMOG2.clone(), mog2.im_fgMaskMOG2);
		if (testMode)
		{
			WindowHandler::GetInstance()->exportAndShowImage("Floodfill", floodfill.im_FloodFill, testMode);
		}

		contours.GetImgContours(framehandler, floodfill.im_FloodFill, im_Frame);

		framehandler.processingFrames(framehandler, im_Frame);

		WindowHandler::GetInstance()->exportAndShowImage("Output", framehandler.im_Final, testMode);

		endTime = clock();
		elapsedSecs = double(endTime - beginTime) / CLOCKS_PER_SEC;
		if (testMode)
		{
			WindowHandler::testImageCntr++;
		}
	}
	capture.release();
	return 0;
}