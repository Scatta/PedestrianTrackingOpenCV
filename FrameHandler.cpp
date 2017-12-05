#include "FrameHandler.h"
#include "stdafx.h"

const int FrameHandler::frameHistorySize = 20;
int FrameHandler::frameCntr = 0;

FrameHandler::FrameHandler()
{
	for (int i = 0; i<frameHistorySize; ++i)
	{
		Frame* NewFramePtr = new Frame();
		frameVector.push_back(NewFramePtr);
		//http://www.cplusplus.com/forum/beginner/70653/
	}
}


FrameHandler::~FrameHandler()
{
	for (int i = 0; i<frameVector.size(); i++)
	{
		delete frameVector.at(i);
	}
	
	if (!frameObjectVector.empty())
	{
		for (int i = 0; i < frameObjectVector.size(); i++)
		{
			delete frameObjectVector.at(i);
		}
	}
}

void FrameHandler::processingFrames(FrameHandler& frames, Mat original)
{
	int prevID = 0;
	Point actMiddle = Point(0, 0);
	Point prevMiddle = Point(0, 0);
	double corrOfPrevObj = 0.0;
	ostringstream corrstrs;
	int objectID;
	frames.im_Final = original.clone();

	if (!(frames.frameVector.at(FrameHandler::frameCntr)->frameLocations.empty()))
	{
		for (int i = 0; i < frames.frameVector.at(FrameHandler::frameCntr)->frameLocations.size(); i++)
		{
			for (int j = 0; j < FrameHandler::frameHistorySize; j++)
			{
				prevID = returnPrevCntr(j);
				if ((i < frames.frameVector.at(j)->frameLocations.size()) && (i < frames.frameVector.at(prevID)->frameLocations.size()))
				{
					//Count the middle pixel of the objects (top left + (bottom right - top left) / 2)
					actMiddle = frames.frameVector.at(j)->frameLocations.at(i).tl() + ((frames.frameVector.at(j)->frameLocations.at(i).br() - frames.frameVector.at(j)->frameLocations.at(i).tl()) / 2);
					prevMiddle = frames.frameVector.at(prevID)->frameLocations.at(i).tl() + ((frames.frameVector.at(prevID)->frameLocations.at(i).br() - frames.frameVector.at(prevID)->frameLocations.at(i).tl()) / 2);
					if (WindowHandler::SearchArea > norm(actMiddle - prevMiddle))
					{
						corrOfPrevObj = getCorrelation(frames.frameVector.at(j)->frameImages.at(i), frames.frameVector.at(prevID)->frameImages.at(i));
						if (corrOfPrevObj > ((double)WindowHandler::CompRate / 100.0))	// Existing object
						{
							rectangle(frames.im_Final, frames.frameVector.at(FrameHandler::frameCntr)->frameLocations.at(i).tl(), frames.frameVector.at(FrameHandler::frameCntr)->frameLocations.at(i).br(), CV_RGB(0, 0, 255), 2, 8, 0);
							line(frames.im_Final, actMiddle, prevMiddle, CV_RGB(255, 0, 0), 2, 8);
							objectID = getFrameObjectID(frames, prevMiddle);
							if (objectID != -1)
							{
								frames.frameObjectVector.at(objectID)->LastSeenFrame = FrameHandler::frameCntr;
								putText(frames.im_Final, to_string(objectID), actMiddle, FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
							}
						}
						else    // New object
						{
							FrameObject* NewFrameObjectPtr = new FrameObject(FrameHandler::frameCntr, actMiddle);
							frameObjectVector.push_back(NewFrameObjectPtr);
						}
					}
				}
			}
		}
	}
	increaseFrameCntr();
	deleteGhostObjects(frames);
}

double FrameHandler::getCorrelation(Mat src_base, Mat src_test)
{
	// http://docs.opencv.org/2.4/doc/tutorials/imgproc/histograms/histogram_comparison/histogram_comparison.html

	Mat hsv_base, hsv_test;

	cvtColor(src_base, hsv_base, COLOR_BGR2HSV);
	cvtColor(src_test, hsv_test, COLOR_BGR2HSV);

	/// Using 50 bins for hue and 60 for saturation
	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };

	// hue varies from 0 to 179, saturation from 0 to 255
	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };

	const float* ranges[] = { h_ranges, s_ranges };

	// Use the o-th and 1-st channels
	int channels[] = { 0, 1 };

	/// Histograms
	MatND hist_base;
	MatND hist_test;

	/// Calculate the histograms for the HSV images
	calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
	normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsv_test, 1, channels, Mat(), hist_test, 2, histSize, ranges, true, false);
	normalize(hist_test, hist_test, 0, 1, NORM_MINMAX, -1, Mat());

	return compareHist(hist_base, hist_test, 0);	// Correlation
}

void FrameHandler::increaseFrameCntr()
{
	if (FrameHandler::frameCntr == (FrameHandler::frameHistorySize - 1))
	{
		FrameHandler::frameCntr = 0;
	}
	else
	{
		FrameHandler::frameCntr++;
	}
}

int FrameHandler::returnPrevCntr(int val)
{
	if (val == 0)
	{
		return FrameHandler::frameHistorySize - 1;
	}
	else
	{
		return (val - 1);
	}
}

int FrameHandler::getFrameObjectID(FrameHandler& frames, Point prevMiddle)
{
	for (int i = 0; i<frameObjectVector.size(); i++)
	{
		if (WindowHandler::SearchArea > norm(frames.frameObjectVector.at(i)->MiddlePoint - prevMiddle))
		{
			return i;
		}
	}
	return -1;
}

void FrameHandler::deleteGhostObjects(FrameHandler& frames)
{
	int prevID = returnPrevCntr(FrameHandler::frameCntr);
	for (int i = 0; i<frameObjectVector.size(); i++)
	{
		if (frames.frameObjectVector.at(i)->LastSeenFrame == prevID)
		{
			delete frameObjectVector.at(i);
		}
	}
}