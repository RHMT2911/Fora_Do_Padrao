#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

using namespace std;
using namespace cv;

int main() {

	VideoCapture cam(0);

	namedWindow("img");
	namedWindow("borda");

	Mat img, gray, borda;
	int a, b;
	cvCreateTrackbar("A", "img", 0, 500);
	cvCreateTrackbar("B", "img", 0, 500);
	setTrackbarPos("A", "img", 100);
	setTrackbarPos("B", "img", 100);

	cvMoveWindow("img", 0, 0);
	cvMoveWindow("borda", 700, 0);

	

	while (true) {
		a = getTrackbarPos("A", "img");
		b = getTrackbarPos("B", "img");

		cam.read(img);
	   cvtColor(img, gray, COLOR_RGB2GRAY);
		Canny(gray, borda, a, b);

		flip(img, img, 1);

		rectangle(img, { 0,0 }, { 50,50 }, { 255,255,255 }, 2, cv::LINE_AA, 0);
		rectangle(img, { 590,50 }, { 640,0 }, { 255,255,255 }, 2, cv::LINE_AA, 0);

		putText(img, "OFF", { 0,80 }, CV_FONT_HERSHEY_SIMPLEX, 1, { 255,255,255 }, 2, cv::LINE_AA);
		putText(img, "ON", { 590,80 }, CV_FONT_HERSHEY_SIMPLEX, 1, { 255,255,255 }, 2, cv::LINE_AA);
		
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				if (borda.at<uchar>(i, j) >= 255) {
					printf("ON");
					break;
				}
			}
		}

		for (int i = 0; i < 50; i++) {
			for (int j = 590; j < 640; j++) {
				if (borda.at<uchar>(i, j) >= 255) {
					printf("OFF");
					break;
				}
			}
		}

		imshow("img", img);
        imshow("borda", borda);

		waitKey(30);
	}
	









}