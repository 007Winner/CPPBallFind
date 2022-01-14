
#include "logic_loop.h"
using namespace cv;
using namespace std;

void LogicLoop::video_loop(VideoCapture cap, VideoWriter out) {
	/**
	 * @brief Performs loop logic for identifying ball and locating the ball's region. Writes video to @param out.
	 * @param cap, the input video
	 * @param out, the output video
	*/
	while (true) {
		Mat frame;
		bool ret = cap.read(frame);
		
		if (ret == true) {
			vector<vector<Point>> regions = ShapesFinder::find_regions(frame);

			vector<Point> ball = ShapesFinder::find_ball(frame);

			//cout << ball << endl;

			if (!ball.empty()) {

				int curr_region = ShapesFinder::find_ball_region(ball, regions);
				vector<vector<Point>> v;
				
				if (curr_region >= 1) {
					v.push_back(regions[curr_region - 1]);

					ImgMod::draw_regions(frame, v);
				}

				ImgMod::draw_ball(frame, ball);
				ImgMod::write_text(frame, to_string(curr_region));

				
			}
			out.write(frame);
		}
		else {
			break;
		}


	}

	cap.release();
	out.release();
	destroyAllWindows();

}