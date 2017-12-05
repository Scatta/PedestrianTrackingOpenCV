#include "Contouring.h"
#include "stdafx.h"
#include "WindowHandler.h"

Contouring::Contouring()
{
}


Contouring::~Contouring()
{
}

void Contouring::GetImgContours(FrameHandler& frames, Mat &threshedimg, Mat &original)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	int largest_area = 0;
	int largest_contour_index = 0;
	double objsize = 0;
	frames.frameVector.at(FrameHandler::frameCntr)->frameImages.clear();		// Clear previous data, what is no more needed
	frames.frameVector.at(FrameHandler::frameCntr)->frameLocations.clear();		// Clear previous data, what is no more needed
	findContours(threshedimg, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours.at(i)), contours_poly.at(i), 3, true);
		boundRect.at(i) = boundingRect(Mat(contours_poly.at(i)));
		boundRect.at(i).x += cvRound(boundRect.at(i).width*0.1);
		boundRect.at(i).width = cvRound(boundRect.at(i).width*0.8);
		boundRect.at(i).y += cvRound(boundRect.at(i).height*0.07);
		boundRect.at(i).height = cvRound(boundRect.at(i).height*0.8);
	}

	for (int i = 0; i< contours.size(); i++)
	{
		//drawContours(original, contours_poly, i, CV_RGB(0, 255, 0), 2, 8, hierarchy);
		objsize = norm(boundRect.at(i).tl() - boundRect.at(i).br());
		if (objsize >((double)WindowHandler::ObjMin) && objsize < ((double)WindowHandler::ObjMax))
		{
			frames.frameVector.at(FrameHandler::frameCntr)->frameImages.push_back(original(Rect(boundRect.at(i).tl(), boundRect.at(i).br())));
			frames.frameVector.at(FrameHandler::frameCntr)->frameLocations.push_back(boundRect.at(i));
		}
	}
}