#include "WindowHandler.h"
#include "stdafx.h"

WindowHandler *WindowHandler::instance = 0;
int WindowHandler::SearchArea = 30;
int WindowHandler::CompRate = 85;
int WindowHandler::ObjMin = 30;
int WindowHandler::ObjMax = 200;
const string WindowHandler::WindowName = "Pedestrian tracking";
const string WindowHandler::TrackbarWindowName = "Trackbars";
const int WindowHandler::FRAME_WIDTH = 640;
const int WindowHandler::FRAME_HEIGHT = 480;
int WindowHandler::PressedKey = 0;
int WindowHandler::testImageCntr = 0;
ostringstream WindowHandler::testImageName;

WindowHandler::WindowHandler()
{
}

void WindowHandler::KeyHandler(int key)
{
	
}

void WindowHandler::Help()
{
	cout
		<< "--------------------------------------------------" << endl
		<< "----------------Pedestrian Tracking---------------" << endl
		<< "-----------------powered by OpenCV----------------" << endl
		<< "----------------from Szabados David---------------" << endl
		<< "--------------------------------------------------" << endl
		<< "                       .ohmMMNdo.                 " << endl
		<< "                      sMMMMMMMMMMy`               " << endl
		<< "                     sMMMMMMMMMMMMh               " << endl
		<< "                     NMMMMMMMMMMMMM               " << endl
		<< "                     sMMMMMMMMMMMMh               " << endl
		<< "                      sMMMMMMMMMMy`               " << endl
		<< "                       .+hmNNmho.                 " << endl
		<< "                       .://-`                     " << endl
		<< "                    -smMMMMMMm+`                  " << endl
		<< "                 `/dMMMMMMMMMMMm-                 " << endl
		<< "               -sNMMMMMMMMMMMMMMN-                " << endl
		<< "            `/dMMMMMMMMMMMMMMMMMMN-               " << endl
		<< "          .sNMMMMMMMMMMMMMMMMMMMMMN-              " << endl
		<< "       `/hMMMMMMMMMMMMMMMMMMMMMMMMMN:             " << endl
		<< "      -mMMMMMMMMyMMMMMMMMMMMMMMMMMMMN:            " << endl
		<< "      dMMMMMMm+`:MMMMMMMMMMMMMMmMMMMMN:           " << endl
		<< "     -MMMMMM/   hMMMMMMMMMMMMMd`dMMMMMNo.         " << endl
		<< "     yMMMMMh   -MMMMMMMMMMMMMM: `dMMMMMMMdo.      " << endl
		<< "    .MMMMMM:   yMMMMMMMMMMMMMd   `sNMMMMMMMMd+.   " << endl
		<< "    sMMMMMm   .MMMMMMMMMMMMMM/      :sNMMMMMMMMd+`" << endl
		<< "   `NMMMMM+   sMMMMMMMMMMMMMm`         :yNMMMMMMMd" << endl
		<< "   +MMMMMN`  `NMMMMMMMMMMMMMo             :yNMMMMy" << endl
		<< "   /MMMMM+   oMMMMMMMMMMMMMM:               `:++- " << endl
		<< "    -+s+-    NMMMMMMMMMMMMMMMy`                   " << endl
		<< "            +MMMMMMMMMMMMMMMMMN+                  " << endl
		<< "            mMMMMMMMMMMMMMMMMMMMm:                " << endl
		<< "           :MMMMMMMMMddMMMMMMMMMMMh.              " << endl
		<< "           dMMMMMMMMM: :mMMMMMMMMMMNo`            " << endl
		<< "          -MMMMMMMMMd    +NMMMMMMMMMMm/           " << endl
		<< "          yMMMMMMMMM/     `oNMMMMMMMMMMh.         " << endl
		<< "         .MMMMMMMMMN`       `sMMMMMMMMMMN`        " << endl
		<< "        .mMMMMMMMMMo          .hMMMMMMMMM/        " << endl
		<< "       :NMMMMMMMMMy             mMMMMMMMMd        " << endl
		<< "      +MMMMMMMMMMs              oMMMMMMMMM.       " << endl
		<< "     sMMMMMMMMMM/               .MMMMMMMMMo       " << endl
		<< "   `hMMMMMMMMMN-                 hMMMMMMMMm       " << endl
		<< "  .mMMMMMMMMMm.                  /MMMMMMMMM:      " << endl
		<< " :NMMMMMMMMMh`                   `NMMMMMMMMy      " << endl
		<< "/MMMMMMMMMMs                      sMMMMMMMMN`     " << endl
		<< "NMMMMMMMMM+                       -MMMMMMMMM/     " << endl
		<< "sMMMMMMMN:                         yMMMMMMMN.     " << endl
		<< " /hmMNdo`                           /hNMNdo`      " << endl
		<< endl;
}

void WindowHandler::exportAndShowImage(string name, Mat &img, bool testMode)
{
	imshow(name, img);
	if (testMode)
	{
		testImageName.str("");
		testImageName << "Images/" << name << "_" << testImageCntr << ".jpg";
		imwrite(testImageName.str(), img);
	}
}