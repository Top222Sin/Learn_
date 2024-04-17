#include <iostream>

// #include "st_edge.hpp"
// #include "st_graph_pipline.hpp"
// #include "st_base_graph.hpp"
// #include "st_graph_pipline_template.hpp"
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
        
#if 0
    // #include "st_edge.hpp"
    // // 创建有向图对象
    // using MyGraph = Graph<EdgeList<Edge<0, 1>, Edge<0, 4>, Edge<1, 2>, Edge<1, 3>, Edge<1, 4>, Edge<2, 3>, Edge<3, 4>>>;
    // MyGraph graph;

    // // 打印邻接表
    // graph.printGraph();

    // // 获取指定边的前驱顶点和后继顶点
    // cout << "边 <1, 2> 的前驱顶点：" << MyGraph::getPredecessor<2>() << endl;
    // cout << "边 <1, 2> 的后继顶点：" << MyGraph::getSuccessor<1>() << endl;
#endif

#if 0
    //#include "st_base_graph.hpp"
    // DirectedGraph<int> graph;

    // // 添加顶点
    // graph.addVertex(0);
    // graph.addVertex(1);
    // graph.addVertex(2);
    // graph.addVertex(3);

    // // 添加边
    // graph.addEdge(0, 1);
    // graph.addEdge(0, 2);
    // graph.addEdge(1, 2);
    // graph.addEdge(2, 3);

    // // 打印图
    // graph.printGraph();

    // // 获取某个节点的前一个顶点和后一个顶点
    // int vertexIndex = 2;
    // int previous = graph.getPreviousVertex(vertexIndex);
    // int next = graph.getNextVertex(vertexIndex);

    // cout << "Previous vertex of vertex " << vertexIndex << ": " << previous << endl;
    // cout << "Next vertex of vertex " << vertexIndex << ": " << next << endl;
#endif

#if 0
    // #include "st_graph_pipline.hpp"
    // 创建算法模块
    AlgorithmModule* initModule = new AlgorithmModule("Initialization");
    AlgorithmModule* preprocessModule = new AlgorithmModule("Data Preprocessing");
    AlgorithmModule* featureModule = new AlgorithmModule("Feature Extraction");
    AlgorithmModule* trainModule = new AlgorithmModule("Model Training");
    AlgorithmModule* evaluateModule = new AlgorithmModule("Model Evaluation");
    AlgorithmModule* outputModule = new AlgorithmModule("Result Output");

    // 构建有向图
    DirectedGraph graph;
    graph.addEdge(initModule, preprocessModule);
    graph.addEdge(preprocessModule, featureModule);
    graph.addEdge(preprocessModule, trainModule);
    graph.addEdge(featureModule, trainModule);
    graph.addEdge(trainModule, evaluateModule);
    graph.addEdge(evaluateModule, outputModule);

    // 执行拓扑排序
    vector<AlgorithmModule*> order = graph.topologicalSort();

    // 输出排序结果
    if (!order.empty()) {
        cout << "Algorithm Pipeline:" << endl;
        for (const auto& module : order) {
            cout << module->getName() << " -> ";
        }
        cout << "End" << endl;
    }

    // 打印某个节点的前后节点
    AlgorithmModule* targetModule = trainModule;
    AlgorithmModule* previousNode = graph.getPreviousNode(targetModule);
    AlgorithmModule* nextNode = graph.getNextNode(targetModule);

    if (previousNode) {
        cout << "Previous node of " << targetModule->getName() << ": " << previousNode->getName() << endl;
    } else {
        cout << "No previous node of " << targetModule->getName() << endl;
    }

    if (nextNode) {
        cout << "Next node of " << targetModule->getName() << ": " << nextNode->getName() << endl;
    } else {
        cout << "No next node of " << targetModule->getName() << endl;
    }

    // 释放内存
    delete initModule;
    delete preprocessModule;
    delete featureModule;
    delete trainModule;
    delete evaluateModule;
    delete outputModule;

#endif

#if 0
    // #include "st_graph_pipline_template.hpp"
    // 创建算法模块
    AlgorithmModule<string>* initModule = new AlgorithmModule<string>("Initialization");
    AlgorithmModule<string>* preprocessModule = new AlgorithmModule<string>("Data Preprocessing");
    AlgorithmModule<string>* featureModule = new AlgorithmModule<string>("Feature Extraction");
    AlgorithmModule<string>* trainModule = new AlgorithmModule<string>("Model Training");
    AlgorithmModule<string>* evaluateModule = new AlgorithmModule<string>("Model Evaluation");
    AlgorithmModule<string>* outputModule = new AlgorithmModule<string>("Result Output");

    // 构建有向图
    DirectedGraph<string> graph;
    graph.addEdge(initModule, preprocessModule);
    graph.addEdge(preprocessModule, featureModule);
    graph.addEdge(preprocessModule, trainModule);
    graph.addEdge(featureModule, trainModule);
    graph.addEdge(trainModule, evaluateModule);
    graph.addEdge(evaluateModule, outputModule);

    // 执行拓扑排序
    vector<AlgorithmModule<string>*> order = graph.topologicalSort();

    // 输出排序结果
    if (!order.empty()) {
        cout << "Algorithm Pipeline:" << endl;
        for (const auto& module : order) {
            cout << module->getName() << " -> ";
        }
        cout << "End" << endl;
    }

    // 打印某个节点的前后节点
    AlgorithmModule<string>* targetModule = trainModule;
    AlgorithmModule<string>* previousNode = graph.getPreviousNode(targetModule);
    AlgorithmModule<string>* nextNode = graph.getNextNode(targetModule);

    if (previousNode) {
        cout << "Previous node of " << targetModule->getName() << ": " << previousNode->getName() << endl;
    } else {
        cout << "No previous node of " << targetModule->getName() << endl;
    }

    if (nextNode) {
        cout << "Next node of " << targetModule->getName() << ": " << nextNode->getName() << endl;
    } else {
        cout << "No next node of " << targetModule->getName() << endl;
    }

    // 释放内存
    delete initModule;
    delete preprocessModule;
    delete featureModule;
    delete trainModule;
    delete evaluateModule;
    delete outputModule;
#endif

    // #include "st_test.hpp"
    ConcreteModule<int, std::string> module1;
    ConcreteModule<std::string, bool> module2;
    ConcreteModule<double, bool> module3;

    // 模拟数据
    int data1 = 42;
    std::string data2 = "Hello";
    double data3 = 3.14;

    // 调用模块
    std::string result1 = module1.process(data1);
    bool result2 = module2.process(data2);
    bool result3 = module3.process(data3);

    std::cout << "Result from module 1: " << result1 << std::endl;
    std::cout << "Result from module 2: " << (result2 ? "true" : "false") << std::endl;
    std::cout << "Result from module 3: " << (result3 ? "true" : "false") << std::endl;


    return 0;
}