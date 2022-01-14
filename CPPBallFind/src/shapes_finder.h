#pragma once
#ifndef SHAPES_FINDER_H
#define SHAPES_FINDER_H
#include <opencv2/opencv.hpp>
#include <math.h>
#include <stdio.h>

using namespace std;
using namespace cv;

class ShapesFinder {
public:
	static vector<vector<Point>> cntfind(cv::Mat img, int size);
	static vector<Point> find_ball(Mat img);
	static Point cnt_center(vector<Point> cnt);
	static vector<vector<Point>> order_regions(vector<vector<Point>> regions);
	static vector<vector<Point>> find_regions(Mat img);
	static float distance(Point p1, Point p2);
	static int calc_nearest_region_midpt(Point pt, vector<vector<Point>> contours);
	static vector<vector<Point>> remove_concavity(vector<vector<Point>> contours);
	static int find_ball_region(vector<Point> ball, vector<vector<Point>> regions);
};


class ImgMod {
public:
	static Mat motionmask(Mat img);
	static void draw_ball(Mat img, vector<Point> cnt);
	static Mat make_border(Mat img);
	static void draw_regions(Mat img, vector<vector<Point>> regions, int thickness = 5);
	static void write_text(Mat img, String text, Point org = Point(200, 200), int fontFace = FONT_HERSHEY_COMPLEX, float fontScale = 3.0, Scalar color = Scalar(125, 246, 55), int thickness = 3);
};

#endif