#include "CPPBallFind.h"

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	if (argc != 2) {
		cout << "Built" << endl;
	}
	else {
		auto path = filesystem::current_path();
		String in_path = path.string() + "/" + argv[1];
		String out_path = path.string() + "/out.avi";

		auto start = chrono::high_resolution_clock::now();
		VideoCapture input_vid(in_path);
		Size size = Size(input_vid.get(3), input_vid.get(4));
		VideoWriter video(out_path, VideoWriter::fourcc('X', 'V', 'I', 'D'), 30, size);

		LogicLoop::video_loop(input_vid, video);

		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
		cout << duration.count() << endl;

		cout << "Done" << endl;
	}
	

	return 0;
}