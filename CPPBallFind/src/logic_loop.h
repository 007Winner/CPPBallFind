#pragma once
#ifndef LOGIC_LOOP_H
#define LOGIC_LOOP_H
#include "shapes_finder.h"

using namespace cv;
using namespace std;


class LogicLoop {
public:
	static void video_loop(VideoCapture cap, VideoWriter out);

};



#endif