#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include "tserial.h"
#include "bot_control.h"

using namespace std;
using namespace cv;
serial comm;
char com[4];



void Arduino(char data) {
	
	comm.startDevice(com, 9600);
	comm.send_data(data);
	comm.stopDevice();
}

int main() {
	com[0] = 'C';
	com[1] = 'O';
	com[2] = 'M';
	com[3] = '6';
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
					printf("ON\n");
					Arduino('L');
					break;
				}
			}
		}

		for (int i = 0; i < 50; i++) {
			for (int j = 590; j < 640; j++) {
				if (borda.at<uchar>(i, j) >= 255) {
					printf("OF\n");
					Arduino('D');
					break;
				}
			}
		}

		imshow("img", img);
        imshow("borda", borda);
		if (_kbhit()) {
			int a;
			printf("Digite o valor da sua porta");
			printf("\n1 - COM1");
			printf("\n2 - COM2");
			printf("\n3 - COM3");
			printf("\n4 - COM4");
			printf("\n5 - COM5");
			printf("\n6 - COM6\n");
			fflush(stdin);
			scanf("%i", &a);
			switch (a)
			{
			case 1:
				com[3] = '1';
				break;
			case 2:
				com[3] = '2';
				break;
			case 3:
				com[3] = '3';
				break;
			case 4:
				com[3] = '4';
				break;
			case 5:
				com[3] = '5';
				break;
			case 6:
				com[3] = '6';
				break;
			case 7:
				com[3] = '7';
				break;
			case 8:
				com[3] = '8';
				break;
			case 9:
				com[3] = '9';
				break;
			default:
				com[3] = '6';
				break;
			}
		}
		waitKey(30);
	}
	









}