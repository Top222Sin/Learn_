#ifndef ST_EDGE_HPP
#define ST_EDGE_HPP

#include <iostream>
#include <vector>

using namespace std;

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
template <typename EdgeList>
class Graph;

// 有向图类特化模板
template <typename... Edges>
class Graph<EdgeList<Edges...>> {
private:
    static const int V = 5; // 结点数量
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

    // 获取指定边的前驱顶点
    template <int Dest>
    static constexpr int getPredecessor() {
        int predecessor = -1;
        (..., [&] {
            if constexpr (Edges::destination == Dest)
                predecessor = Edges::source;
        }());
        return predecessor;
    }

    // 获取指定边的后继顶点
    template <int Src>
    static constexpr int getSuccessor() {
        int successor = -1;
        (..., [&] {
            if constexpr (Edges::source == Src)
                successor = Edges::destination;
        }());
        return successor;
    }

};



#endif // ST_TEST_HPP
