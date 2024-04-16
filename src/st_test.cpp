#include <iostream>

#include "st_test.hpp"

// Eigen
#include <Eigen/Dense>

// // NCNN
// #include "net.h"
// #include "simpleocv.h"

// OpenCV
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;
using namespace cv;

int main(int argc, char** argv) {

    // example_0
    cout << "Hello, World!" << endl;

    // example_1 eigen
#if 0
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    cout << m << endl;
#endif

     // example_2 ncnn
#if 0
    ncnn::Net net;
#endif

    // example_3 opencv
#if 0
    // 定义文件路径
    std::string imagePath = "demo.jpg";

    //读取图片（使用图片的绝对路径）
    cv::Mat src = cv::imread(imagePath, cv::IMREAD_COLOR);
    if(src.empty()) {
        std::cerr << "Could not open or find the src" << std::endl;
        return -1;
    }else{
        std::cout << "src loaded successfully" << std::endl;    
    }
    
	//显示图片
	imshow("Output",src);
	
    //显示灰度图
	Mat Gray;
	cvtColor(src, Gray, 6);
	imshow("Gray",Gray);
	
	//不加此语句图片会一闪而过
	waitKey(0);

#endif

    // example_3 graph
    // 创建一个有5个顶点的有向图
    Graph<int> g(5);

    // 插入边
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    std::cout << "Graph edges:" << std::endl;
    g.printGraph();

    std::cout << "BFS Traversal starting from vertex 0:" << std::endl;
    g.bfs(0);

    return 0;
}