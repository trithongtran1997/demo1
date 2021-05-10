#include <iostream>

#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>


#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;
int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;

int main() {
	Mat imgblur, imgcanny, imggray, mask;
	Mat img = imread("b.jpg");
	cvtColor(img, imggray, COLOR_BGR2HSV);
	Scalar lower(hmin, smin, vmin);
	Scalar upper(hmax, smax, vmax);
	inRange(imggray, lower, upper, mask);
	blur(imggray, imgblur, Size(3, 3));
	Canny(imgblur, imgcanny, 0, 150 ,3);
	vector<vector<Point> > contours;
	findContours(imgcanny, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	RNG rng(12345);
	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(contours[i], contours_poly[i], 3, true);
		boundRect[i] = boundingRect(contours_poly[i]);
	}
	Mat drawing = Mat::zeros(imgcanny.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours_poly, (int)i, color);
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2);
	}
	imshow("Contours", drawing);
	waitKey(0);
}