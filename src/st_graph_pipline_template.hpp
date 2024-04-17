#ifndef ST_GRAPH_PIPELINE_TEMPLATE_HPP
#define ST_GRAPH_PIPELINE_TEMPLATE_HPP


#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// 顶点表示算法模块
template<typename T>
class AlgorithmModule {
private:
    T name;

public:
    AlgorithmModule(T n) : name(n) {}

    T getName() const {
        return name;
    }
};

// 有向图类
template<typename T>
class DirectedGraph {
private:
    unordered_map<AlgorithmModule<T>*, vector<AlgorithmModule<T>*>> adjList;

public:
    // 添加有向边
    void addEdge(AlgorithmModule<T>* from, AlgorithmModule<T>* to) {
        adjList[from].push_back(to);
    }

    // 拓扑排序
    vector<AlgorithmModule<T>*> topologicalSort() {
        unordered_map<AlgorithmModule<T>*, int> inDegree;
        for (const auto& pair : adjList) {
            for (const auto& neighbor : pair.second) {
                inDegree[neighbor]++;
            }
        }

        queue<AlgorithmModule<T>*> q;
        for (const auto& pair : adjList) {
            if (inDegree.find(pair.first) == inDegree.end()) {
                q.push(pair.first);
            }
        }

        vector<AlgorithmModule<T>*> order;
        while (!q.empty()) {
            AlgorithmModule<T>* module = q.front();
            q.pop();
            order.push_back(module);

            for (const auto& neighbor : adjList[module]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        if (order.size() != adjList.size()) {
            cout << "Cycle detected! Topological sorting not possible." << endl;
            return vector<AlgorithmModule<T>*>();
        }

        return order;
    }

    // 获取某个节点的前一个节点
    AlgorithmModule<T>* getPreviousNode(AlgorithmModule<T>* node) {
        for (const auto& pair : adjList) {
            for (const auto& neighbor : pair.second) {
                if (neighbor == node) {
                    return pair.first;
                }
            }
        }
        return nullptr;
    }

    // 获取某个节点的后一个节点
    AlgorithmModule<T>* getNextNode(AlgorithmModule<T>* node) {
        if (adjList.find(node) != adjList.end() && !adjList[node].empty()) {
            return adjList[node][0]; // 返回第一个后继节点
        }
        return nullptr;
    }
};



#endif // ST_GRAPH_PIPELINE_TEMPLATE_HPP

