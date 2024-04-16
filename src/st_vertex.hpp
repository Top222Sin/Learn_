#ifndef ST_VERTEX_HPP
#define ST_VERTEX_HPP


#include <iostream>
#include <vector>

using namespace std;

// 顶点的结构体模板
template <int Index>
struct Vertex {
    static const int index = Index;
};

// 边的结构体模板
template <int Src, int Dest>
struct Edge {
    static const int source = Src;
    static const int destination = Dest;
};

// 边的列表模板
template <typename... Edges>
struct EdgeList {};

// 边的列表递归模板
template <typename Edge, typename... Edges>
struct EdgeList<Edge, Edges...> {
    static void addEdge(vector<vector<int>>& adjList) {
        adjList[Edge::source].push_back(Edge::destination);
        EdgeList<Edges...>::addEdge(adjList);
    }
};

// 边的列表递归终止条件
template <>
struct EdgeList<> {
    static void addEdge(vector<vector<int>>& adjList) {}
};

// 有向图类模板
template <typename... Vertices, typename... Edges>
class Graph {
private:
    static const int V = sizeof...(Vertices); // 结点数量
    vector<vector<int>> adjList; // 邻接表

public:
    // 构造函数
    Graph() {
        adjList.resize(V);
        EdgeList<Edges...>::addEdge(adjList);
    }

    // 打印邻接表
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            cout << "顶点 " << i << " 的邻接表：";
            for (int dest : adjList[i]) {
                cout << " -> " << dest;
            }
            cout << endl;
        }
    }

    // 获取指定顶点的入度
    template <int Index>
    constexpr int getInDegree() {
        int inDegree = 0;
        for (int i = 0; i < V; ++i) {
            for (int dest : adjList[i]) {
                if (dest == Index) {
                    ++inDegree;
                }
            }
        }
        return inDegree;
    }

    // 获取指定顶点的出度
    template <int Index>
    constexpr int getOutDegree() {
        return adjList[Index].size();
    }
};





#endif // ST_VERTEX_HPP
