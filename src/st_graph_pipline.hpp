#ifndef ST_GRAPH_PIPELINE_HPP
#define ST_GRAPH_PIPELINE_HPP


#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// 顶点表示算法模块
class AlgorithmModule {
private:
    string name;

public:
    AlgorithmModule(string n) : name(n) {}

    string getName() const {
        return name;
    }
};

// 有向图类
class DirectedGraph {
private:
    unordered_map<AlgorithmModule*, vector<AlgorithmModule*>> adjList;

public:
    // 添加有向边
    void addEdge(AlgorithmModule* from, AlgorithmModule* to) {
        adjList[from].push_back(to);
    }

    // 拓扑排序
    vector<AlgorithmModule*> topologicalSort() {
        unordered_map<AlgorithmModule*, int> inDegree;
        for (const auto& pair : adjList) {
            for (const auto& neighbor : pair.second) {
                inDegree[neighbor]++;
            }
        }

        queue<AlgorithmModule*> q;
        for (const auto& pair : adjList) {
            if (inDegree.find(pair.first) == inDegree.end()) {
                q.push(pair.first);
            }
        }

        vector<AlgorithmModule*> order;
        while (!q.empty()) {
            AlgorithmModule* module = q.front();
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
            return vector<AlgorithmModule*>();
        }

        return order;
    }

    // 获取某个节点的前一个节点
    AlgorithmModule* getPreviousNode(AlgorithmModule* node) {
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
    AlgorithmModule* getNextNode(AlgorithmModule* node) {
        if (adjList.find(node) != adjList.end() && !adjList[node].empty()) {
            return adjList[node][0]; // 返回第一个后继节点
        }
        return nullptr;
    }
};






#endif // ST_VERTEX_HPP
