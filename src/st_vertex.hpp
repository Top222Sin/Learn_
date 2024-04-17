#ifndef ST_VERTEX_HPP
#define ST_VERTEX_HPP


#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class DirectedGraph {
public:
    struct Vertex {
        T data; // 顶点数据
        std::vector<Vertex*> outgoingEdges; // 存储从该顶点出发的有向边的目标顶点
    };

    // 添加顶点
    void addVertex(const T& value) {
        vertices.push_back(new Vertex{value});
    }

    // 添加有向边，假设顶点已经存在
    void addEdge(Vertex* source, Vertex* destination) {
        source->outgoingEdges.push_back(destination);
    }

    // 删除有向边
    bool removeEdge(Vertex* source, Vertex* destination) {
        auto it = std::find(source->outgoingEdges.begin(), source->outgoingEdges.end(), destination);
        if (it != source->outgoingEdges.end()) {
            source->outgoingEdges.erase(it);
            return true;
        }
        return false;
    }

    // 删除顶点及其关联的边
    void removeVertex(Vertex* vertexToRemove) {
        // 需要先删除所有指向该顶点的边（此处未实现）
        // ...
        auto it = std::find_if(vertices.begin(), vertices.end(), [vertexToRemove](const Vertex* v) { return v == vertexToRemove; });
        if (it != vertices.end()) {
            delete *it;
            vertices.erase(it);
        }
    }

    // 打印邻接表
    void printGraph() {
        for (const auto& vertex : vertices) {
            std::cout << "顶点 " << vertex->data << " 的邻接顶点：";
            for (const auto& edge : vertex->outgoingEdges) {
                std::cout << edge->data << " ";
            }
            std::cout << std::endl;
        }
    }

    // // 获取指定边的前驱顶点
    // template<T value>
    // static T getPredecessor() {
    //     return Edge<value>::predecessor;
    // }

    // // 获取指定边的后继顶点
    // template<T value>
    // static T getSuccessor() {
    //     return Edge<value>::successor;
    // }



    std::vector<Vertex*> vertices; // 顶点容器
};





#endif // ST_VERTEX_HPP
