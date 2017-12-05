#include "TrackbarHandler.h"
#include "stdafx.h"
#include "WindowHandler.h"

TrackbarHandler *TrackbarHandler::instance = 0;

TrackbarHandler::TrackbarHandler()
{
}

void on_trackbar(int, void*)
{
}

void TrackbarHandler::createTrackbars() {
	namedWindow(WindowHandler::TrackbarWindowName, WINDOW_AUTOSIZE);
	ostringstream TrackbarName;
	TrackbarName << "SearchArea " << WindowHandler::SearchArea;
	TrackbarName << "CompareRate " << WindowHandler::CompRate;
	TrackbarName << "ObjMinSize " << WindowHandler::ObjMin;
	TrackbarName << "ObjMaxSize " << WindowHandler::ObjMax;
	createTrackbar("SearchArea", WindowHandler::TrackbarWindowName, &WindowHandler::SearchArea, 255, on_trackbar);
	createTrackbar("CompRate", WindowHandler::TrackbarWindowName, &WindowHandler::CompRate, 100, on_trackbar);
	createTrackbar("ObjMinSize", WindowHandler::TrackbarWindowName, &WindowHandler::ObjMin, 500, on_trackbar);
	createTrackbar("ObjMaxSize", WindowHandler::TrackbarWindowName, &WindowHandler::ObjMax, 500, on_trackbar);
}
