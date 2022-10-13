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
			
			for (int h = 0; h < faces.size(); h++) {				
		
				rectangle(img, faces[h].tl(), faces[h].br(), Scalar(50, 50, 50), 3);
				#pragma omp parallel for
				for( int a=0;a<=20;a++){
				//#pragma omp parallel for
					for( int i = faces[h].x; i < faces[h].x + faces[h].width ; ++i) { 
							//#pragma omp parallel for
							for( int j = faces[h].y; j < faces[h].y + faces[h].height; ++j) { 
								int p0ul=img.at<Vec3b>(j-1 ,i-1).val[0];
								int p0uc=img.at<Vec3b>(j-1 ,i).val[0];
								int p0ur=img.at<Vec3b>(j-1 ,i+1).val[0];
								int p0cl=img.at<Vec3b>(j ,i-1).val[0];
								int p0cc=img.at<Vec3b>(j ,i).val[0];
								int p0cr=img.at<Vec3b>(j ,i+1).val[0];
								int p0dl=img.at<Vec3b>(j+1 ,i-1).val[0];
								int p0dc=img.at<Vec3b>(j+1 ,i).val[0];
								int p0dr=img.at<Vec3b>(j+1 ,i+1).val[0];
								int cero=(p0ul+p0uc+p0ur+p0cl+p0cc+p0cr+p0dl+p0dc+p0dr)/9;

								int p1ul=img.at<Vec3b>(j-1 ,i-1).val[1];
								int p1uc=img.at<Vec3b>(j-1 ,i).val[1];
								int p1ur=img.at<Vec3b>(j-1 ,i+1).val[1];
								int p1cl=img.at<Vec3b>(j ,i-1).val[1];
								int p1cc=img.at<Vec3b>(j ,i).val[1];
								int p1cr=img.at<Vec3b>(j ,i+1).val[1];
								int p1dl=img.at<Vec3b>(j+1 ,i-1).val[1];
								int p1dc=img.at<Vec3b>(j+1 ,i).val[1];
								int p1dr=img.at<Vec3b>(j+1 ,i+1).val[1];
								int uno=(p1ul+p1uc+p1ur+p1cl+p1cc+p1cr+p1dl+p1dc+p1dr)/9;

								int p2ul=img.at<Vec3b>(j-1 ,i-1).val[2];
								int p2uc=img.at<Vec3b>(j-1 ,i).val[2];
								int p2ur=img.at<Vec3b>(j-1 ,i+1).val[2];
								int p2cl=img.at<Vec3b>(j ,i-1).val[2];
								int p2cc=img.at<Vec3b>(j ,i).val[2];
								int p2cr=img.at<Vec3b>(j ,i+1).val[2];
								int p2dl=img.at<Vec3b>(j+1 ,i-1).val[2];
								int p2dc=img.at<Vec3b>(j+1 ,i).val[2];
								int p2dr=img.at<Vec3b>(j+1 ,i+1).val[2];
								int dos=(p2ul+p2uc+p2ur+p2cl+p2cc+p2cr+p2dl+p2dc+p2dr)/9;
														
								img.at<Vec3b>(j ,i).val[0]=cero;
								img.at<Vec3b>(j ,i).val[1]=uno;
								img.at<Vec3b>(j ,i).val[2]=dos;
															
							} 
					}
				}
				 
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