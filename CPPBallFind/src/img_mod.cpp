
#include "shapes_finder.h"

using namespace cv;
using namespace std;

/////GLOBALS///////

Scalar GREEN = Scalar(0, 255, 0);
Scalar BLUE = Scalar(255, 0, 0);
Scalar RED = Scalar(0, 0, 255);

auto OBJECT_DETECTOR = createBackgroundSubtractorMOG2(3, 700, false);

	Mat ImgMod::motionmask(Mat img) {
		/**
		 * @brief masks stationary objects in an image, only moving objects remain
		 * @param img, an image
		 * @return a new image in which non-moving objects will be masked out. Finding contours of mask
		 * will outline those objects that are in motion.
		*/

		Mat mask;
		OBJECT_DETECTOR->apply(img, mask);

		return mask;

}

void ImgMod::draw_ball(Mat img, vector<Point> cnt) {
	/**
	 * @brief Draws box around a contour and red dot at center of the contour onto @param img
	 * @param img, an image
	 * @param cnt, a contour
	*/

	auto rect = boundingRect(cnt);
	auto ball_ctr = ShapesFinder::cnt_center(cnt);

	rectangle(img, rect, GREEN, 3);
	circle(img, ball_ctr, 20, RED, -1);

}

Mat ImgMod::make_border(Mat img) {
	/**
	 * @brief draws border around an image. This is useful to "complete" contours that go out of frame.
	 * @param img, an image
	 * @return the bordered version of @param img
	*/

	auto borderType = BORDER_CONSTANT;
	int top = 20;
	int bottom = top;
	int left = 20;
	int right = left;

	Scalar COLOR = Scalar(255, 255, 255);

	Mat bordered;
	copyMakeBorder(img, bordered, top, bottom, left, right, borderType, COLOR);

	return bordered;

}

void ImgMod::draw_regions(Mat img, vector<vector<Point>> regions, int thickness) {
	/**
	 * @brief draws red outlines around each contour in @param contours
	 * @param img, an image
	 * @param regions, a list of contours
	 * @param thickness, the thickness of the lines that will trace the contours in @param regions
	*/

	drawContours(img, regions, 0, RED, thickness);

}

void ImgMod::write_text(Mat img, String text, Point org, int fontFace, float fontScale, Scalar color, int thickness) {
	/**
	 * @brief Writes text to @param img
	 * @param img, an image
	 * @param text, text to be written to image
	 * @param org, pixel coordinates at which text will be placed, optional. Default is (200,200) -- the top left corner
	 * @param fontFace, the font, optional. Defaults to FONT_HERSHEY_DUPLEX
	 * @param fontScale, the font size, optional. Defaults to 3.0.
	 * @param color, BGR color for the text, optional. Default is light green.
	 * @param thickness, the thickness of the text, optional. The default is 3.
	*/

	putText(img, text, org, fontFace, fontScale, color, thickness);

}