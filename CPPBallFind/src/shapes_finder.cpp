
#include "shapes_finder.h"

using namespace cv;
using namespace std;
////GLOBALS///////
int MAX = 999999999;

//////////////////


vector<vector<Point>> ShapesFinder::cntfind(cv::Mat img, int size) {
	/**
	 * @brief Find sufficiently large contours within an image
	 * @param img, an image
	 * @param size, the min size of contours which will be found on @param img
	 * @return the list of contours that are larger than @param size
	*/
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(img, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	
	int i = 0;
	vector<vector<Point>> big_contours;
	for (auto& cnt : contours) {
		auto area = contourArea(cnt);
		if (i == 0) {
			i = 1;
		}
		else if (area > size) {
			big_contours.push_back(cnt);
		}
	}

	return big_contours;

}

vector<Point> ShapesFinder::find_ball(Mat img) {
	/**
	 * @brief find the ball within the image
	 * @param img, an image 
	 * @return ball_cnt, the contour of the ball. Return an empty vector if no ball is found on @param img
	*/
	Mat mask = ImgMod::motionmask(img);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	auto ball = cntfind(mask, 5000);
	if (ball.size() > 0) {
		vector<Point> ball_cnt = ball[0];
		return ball_cnt;
	}
	else {

		return {};
	}
	

}

Point ShapesFinder::cnt_center(vector<Point> cnt) {
	/**
	 * @brief finds the center of a contour
	 * @param cnt, a contour
	 * @return the pixel coordinate of @param cnt's center
	*/
	auto m = moments(cnt, true);
	Point cnt_ctr(m.m10 / m.m00, m.m01 / m.m00);
	return cnt_ctr;
}

vector<vector<Point>> ShapesFinder::order_regions(vector<vector<Point>> regions) {
	/**
	 * @brief Orders the list of region contours such that they have each
     * contour's index correspond with its court region's official number, as per
     * the game rules. Diagram below
	 * _______
     * |  2  |
     * |1   3|
     * |__4__|
	 * 
	 * @param regions, list of region contours
	 * @return the list of ordered region contours
	*/
	vector<tuple<Point, vector<Point>>> reg_ctr_list;
	
	for (auto& region : regions) {
		auto ctr = cnt_center(region);
		tuple<Point, vector<Point>> tup (ctr, region);
		reg_ctr_list.push_back(tup);
	}

	vector<int> templistx;
	vector<int> templisty;
	for (auto& entry : reg_ctr_list) {
		templistx.push_back(get<0>(entry).x);
		templisty.push_back(get<0>(entry).y);
	}

	vector<vector<Point>> finallist(regions.size());//didn't initialize four values to zeroes oops
	for (auto& entry : reg_ctr_list) {
		if (get<0>(entry).x == *min_element(templistx.begin(), templistx.end())) {
			finallist[0] = get<1>(entry);
		}
		else if (get<0>(entry).x == *max_element(templistx.begin(), templistx.end())) {
			finallist[2] = get<1>(entry);
		}
		else if (get<0>(entry).y == *min_element(templisty.begin(), templisty.end())) {
			finallist[1] = get<1>(entry);
		}
		else {
			finallist[3] = get<1>(entry);
		}
	}
	return finallist;
}

vector<vector<Point>> ShapesFinder::find_regions(Mat img) {
	/**
	 * @brief Finds the contours for the court regions
	 * @param img, an image
	 * @return the list of contours that contains a contour for each court region
	*/

	Mat bordered = ImgMod::make_border(img);
	Mat gray;
	cvtColor(bordered, gray, COLOR_BGR2GRAY);
	Mat thresh;
	threshold(gray, thresh, 127, 255, THRESH_BINARY);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> regions = cntfind(thresh, 100000);

	//Translate the coordinates to account for the offset from the border
	for (auto& region : regions) {

		for (auto& pt : region) {
			pt.x = pt.x - 20;
			pt.y = pt.y - 20;
		}

	}

	//cv2 findContours finds contours in different orders on each frame,
	//so we must order the contours on each frame

	regions = order_regions(regions);
	regions = remove_concavity(regions);
	return regions;
}

float ShapesFinder::distance(Point p1, Point p2) {
	/**
	 * @brief calculates euclidian distance between points
	 * @param p1, a cv::Point
	 * @param p2, a cv::Point
	 * @return distance between p1 and p2
	*/
	float dist = sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2));
	return dist;
}

int ShapesFinder::calc_nearest_region_midpt(Point pt, vector<vector<Point>> contours) {
	/**
	 * @brief finds contour with closest center to a point
	 * @param pt, a cv::Point
	 * @param contours, a list of contours
	 * @return the index of the contour in @param contours which is the shortest euclidian distance to @param point
	*/

	vector<Point> ctr_list;
	for (auto& cnt : contours) {
		ctr_list.push_back(cnt_center(cnt));
	}

	vector<int> distances(MAX, contours.size());

	for (int index = 0; index < ctr_list.size(); index++) {
		distances[index] = distance(pt, ctr_list[index]);
	}

	for (int index = 0; index < ctr_list.size(); index++) {
		if (distances[index] == *min_element(distances.begin(), distances.end())) {
			return index + 1;
		}
	}

	return -1;
}

vector<vector<Point>> ShapesFinder::remove_concavity(vector<vector<Point>> contours) {
	/**
	 * @brief removes concave "holes" within contours using convex hulls. These hulls are the approximate shapes of @param contours.
	 * @param contours a list of contours
	 * @return the list of contex hulls of the contours.
	*/
	vector<vector<Point>> convex_hull_contours;

	for (auto& cnt : contours) {
		vector<Point> cHull;
		convexHull(cnt, cHull);
		convex_hull_contours.push_back(cHull);
	}

	return convex_hull_contours;
}

int ShapesFinder::find_ball_region(vector<Point> ball, vector<vector<Point>> regions) {
	/**
	 * @brief Finds the region in which the ball contour is located.
	 * @param ball, the contour of the ball
	 * @param regions, list of contours -- one contour for each court region
	 * @return the index of the region in which @param ball's center is located.
	*/

	auto ball_ctr = cnt_center(ball);

	for (int index = 0; index < regions.size(); index++) {
		int isinregion = pointPolygonTest(regions[index], ball_ctr, false);
		if (isinregion == 1) {
			return index + 1;
		}

	}
	return -1;

}
