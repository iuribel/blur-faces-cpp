#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>
#include <time.h>
#include <stdio.h>
#include <chrono>
#include <sys/time.h>
#include <ctime>
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

using namespace std;
using namespace cv;


void Gauss() {
	
}

int main(int argc, const char** argv){

	char* rutaVideoIn = (char*) malloc(30*sizeof(char));
	strcat(strcpy(rutaVideoIn, "./"), argv[1]);

	printf("%s", rutaVideoIn);

	cv::VideoCapture cap(0);
	CascadeClassifier facedetect;


	//cap.open(rutaVideoIn);

	if(!cap.isOpened()){
		printf("error");
	}else{
			
		
		printf("entrooooo");
		int iter=100;
		Mat img;
		facedetect.load("haarcascade_frontalface_default.xml");
		while (true) {
			
			auto start = std::chrono::high_resolution_clock::now();
			cap.read(img);

			vector<Rect> faces;

			facedetect.detectMultiScale(img, faces, 1.3, 5);

			//
			#pragma omp parallel for
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
			
			auto end = std::chrono::high_resolution_clock::now();
			cout << "Elapsed time in milliseconds: "
			<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
			<< " ms" << endl;
			cout << faces.size() << endl;
		}
	}

}