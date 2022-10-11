#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>
#include <time.h>
#include <stdio.h>


using namespace std;
using namespace cv;


/*void main() {
	string path = "chando.jpg";
	Mat	img = imread(path);
	imshow("Frame", img);
	waitKey(0);
}*/

int main(int argc, const char** argv){

	char* rutaVideoIn = (char*) malloc(30*sizeof(char));
	strcat(strcpy(rutaVideoIn, "./"), argv[1]);

	printf("%s", rutaVideoIn);

	cv::VideoCapture cap(0);
	CascadeClassifier facedetect;

	String name = cap.getBackendName();
	//cap.open(rutaVideoIn);

	if(!cap.isOpened()){
		printf("error");
	}else{
		
		
		
		printf("entrooooo");
		Mat img;
		facedetect.load("haarcascade_frontalface_default.xml");
		while (true) {
			
			
			cap.read(img);

			vector<Rect> faces;

			facedetect.detectMultiScale(img, faces, 1.3, 5);

			cout << faces.size() << endl;

			for (int i = 0; i < faces.size(); i++) {				
		
				rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50, 50, 50), 3);
				cv::Point topLeft = cv::Point(faces[i].x, faces[i].y);
				cv::Point bottomRight = cv::Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
				cv::Rect roi = cv::Rect(topLeft, bottomRight);
				cv::GaussianBlur(img(roi), img(roi), cv::Size(51, 51), 0);
				rectangle(img, Point(0,0), Point(250,70), Scalar(50, 50, 255));
				putText(img, to_string(faces.size())+" Face Found", Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1);
				
			}

			
			imshow("Frame", img);
			waitKey(1);
			
			
			
		
		}
	}

}