#pragma once
#include <vector>
namespace _Graph {
struct _Graph {
    struct Node {
        int v, nxt;
    };
    std::vector<int> head;
    std::vector<Node> edge;
    _Graph() {
    }
    _Graph(int n) : head(n, -1){};
    void add(int u, int v) {
        edge.emplace_back(Node{v, head[u]});
        head[u] = edge.size() - 1;
    }
};
struct _WGraph {
    struct Node {
        int v, w, nxt;
    };
    std::vector<int> head;
    std::vector<Node> edge;
    _WGraph() {
    }
    _WGraph(int n) : head(n, -1){};
    void add(int u, int v, int w) {
        edge.emplace_back(Node{v, w, head[u]});
        head[u] = edge.size() - 1;
    }
};
struct _WCGraph {
    struct Node {
        int v, w, c, nxt;
    };
    std::vector<int> head;
    std::vector<Node> edge;
    _WCGraph() {
    }
    _WCGraph(int n) : head(n, -1){};
    void add(int u, int v, int w, int c) {
        edge.emplace_back(Node{v, w, c, head[u]});
        head[u] = edge.size() - 1;
    }
};
} // namespace _Graph
