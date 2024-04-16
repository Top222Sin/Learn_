#include <iostream>

// #include "st_edge.hpp"
#include "st_vertex.hpp"

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
        
    // // 创建有向图对象
    // using MyGraph = Graph<EdgeList<Edge<0, 1>, Edge<0, 4>, Edge<1, 2>, Edge<1, 3>, Edge<1, 4>, Edge<2, 3>, Edge<3, 4>>>;
    // MyGraph graph;

    // // 打印邻接表
    // graph.printGraph();

    // // 获取指定边的前驱顶点和后继顶点
    // cout << "边 <1, 2> 的前驱顶点：" << MyGraph::getPredecessor<2>() << endl;
    // cout << "边 <1, 2> 的后继顶点：" << MyGraph::getSuccessor<1>() << endl;


    // 创建有向图对象
    using MyGraph = Graph<Vertex<0>, Vertex<1>, Vertex<2>, Vertex<3>, Vertex<4>,
                          Edge<0, 1>, Edge<0, 4>, Edge<1, 2>, Edge<1, 3>, Edge<1, 4>, Edge<2, 3>, Edge<3, 4>>;

    // 使用已创建的有向图对象
    MyGraph graph;

    // 打印邻接表
    graph.printGraph();

    // 获取指定顶点的入度和出度
    cout << "顶点 2 的入度：" << graph.getInDegree<2>() << endl;
    cout << "顶点 2 的出度：" << graph.getOutDegree<2>() << endl;


    return 0;
}