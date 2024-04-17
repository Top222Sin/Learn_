#ifndef ST_BASE_GRAPH_HPP
#define ST_BASE_GRAPH_HPP

#include <iostream>
#include <vector>

using namespace std;

// 模板类，表示图中的每个顶点
template<typename T>
struct Vertex {
    T data;
    vector<int> edges;

    Vertex(T d) : data(d) {}
};

// 模板类，表示有向图
template<typename T>
class DirectedGraph {
private:
    vector<Vertex<T>> vertices; // 存储图中的所有顶点

public:
    // 添加顶点到图中
    void addVertex(T data) {
        Vertex<T> v(data);
        vertices.push_back(v);
    }

    // 添加边到图中
    void addEdge(int from, int to) {
        // 确保顶点索引的有效性
        if (from < 0 || from >= vertices.size() || to < 0 || to >= vertices.size()) {
            cout << "Invalid vertex index!" << endl;
            return;
        }
        vertices[from].edges.push_back(to);
    }

    // 获取某个节点的前一个顶点
    T getPreviousVertex(int vertexIndex) {
        if (vertexIndex < 0 || vertexIndex >= vertices.size()) {
            cout << "Invalid vertex index!" << endl;
            return T();
        }
        if (vertexIndex == 0) {
            cout << "No previous vertex for the first vertex!" << endl;
            return T();
        }
        return vertices[vertexIndex - 1].data;
    }

    // 获取某个节点的后一个顶点
    T getNextVertex(int vertexIndex) {
        if (vertexIndex < 0 || vertexIndex >= vertices.size()) {
            cout << "Invalid vertex index!" << endl;
            return T();
        }
        if (vertexIndex == vertices.size() - 1) {
            cout << "No next vertex for the last vertex!" << endl;
            return T();
        }
        return vertices[vertexIndex + 1].data;
    }

    // 打印图的邻接表表示
    void printGraph() {
        cout << "Directed Graph (Adjacency List):" << endl;
        for (int i = 0; i < vertices.size(); ++i) {
            cout << "Vertex " << vertices[i].data << " --> ";
            for (int j = 0; j < vertices[i].edges.size(); ++j) {
                cout << vertices[i].edges[j] << " ";
            }
            cout << endl;
        }
    }
};





#endif // ST_BASE_GRAPH_HPP
