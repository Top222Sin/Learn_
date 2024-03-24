#include <iostream>

// Eigen
#include <Eigen/Dense>

// NCNN
#include "net.h"
#include "simpleocv.h"

// OpenCV
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;
using namespace cv;

int main(int argc, char** argv) {

    // example_0
    cout << "Hello, World!" << endl;

    // example_1 eigen
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    cout << m << endl;

    // example_2 ncnn
    ncnn::Net net;


    // example_3 opencv
    //读取图片（使用图片的绝对路径）
	// Mat src = imread("demo.jpg");
    cv::Mat src = cv::imread("demo.jpg", cv::IMREAD_COLOR);
    if(src.empty()) {
        std::cerr << "Could not open or find the src" << std::endl;
        return -1;
    }
    std::cout << "src loaded successfully" << std::endl;

	//显示图片
	imshow("Output",src);
	
    //显示灰度图
	Mat Gray;
	cvtColor(src, Gray, 6);
	imshow("Gray",Gray);
	
	//不加此语句图片会一闪而过
	waitKey(0);


    return 0;
}