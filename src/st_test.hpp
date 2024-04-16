#ifndef ST_TEST_HPP
#define ST_TEST_HPP

#include <iostream>
#include <vector>
#include <queue>

template<typename T>
class Graph {
public:
    struct Node {
        T vertex;
        std::vector<T> neighbors;
    };

    void addEdge(T src, T dest) {
        nodes[src].neighbors.push_back(dest);
    }

    void printGraph() {
        for (const auto& node : nodes) {
            std::cout << "Vertex: " << node.vertex << ", Neighbors: ";
            for (T neighbor : node.neighbors) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

    void bfs(T startNode) {
        std::vector<bool> visited(nodes.size(), false);
        std::queue<T> queue;

        visited[startNode] = true;
        queue.push(startNode);

        while (!queue.empty()) {
            T current = queue.front();
            queue.pop();

            std::cout << "Visited: " << current << std::endl;

            for (T neighbor : nodes[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }
    }
    
    std::vector<Node> nodes; // 初始化为空，节点数量不确定，故用vector存储

    // 构造函数初始化nodes，假设有n个顶点
    Graph(size_t n) {
        nodes.resize(n);
        for (size_t i = 0; i < n; ++i) {
            nodes[i].vertex = static_cast<T>(i);
        }
    }
};



#endif // ST_TEST_HPP
