#pragma once
#include <vector>
namespace _Graph_nxt {
struct _Graph {
    struct Node {
        int v, nxt;
    };
    std::vector<int> head;
    std::vector<Node> edge;
    _Graph() {
    }
    _Graph(int n) : head(n + 1, -1){};
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
    _WGraph(int n) : head(n + 1, -1){};
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
    _WCGraph(int n) : head(n + 1, -1){};
    void add(int u, int v, int w, int c) {
        edge.emplace_back(Node{v, w, c, head[u]});
        head[u] = edge.size() - 1;
    }
};
struct Graph : public _WGraph {
    void add_flow(int u, int v, int w) {
        add(u, v, w);
        add(v, u, 0);
    }
};
} // namespace _Graph_nxt
namespace _Graph_edge {
struct _Graph {
    std::vector<std::vector<int>> edge;
    _Graph() {
    }
    _Graph(int n) : edge(n + 1){};
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
};
struct _WGraph {
    struct Node {
        int v, w;
    };

    std::vector<std::vector<Node>> edge;
    _WGraph() {
    }
    _WGraph(int n) : edge(n + 1){};
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
};
struct _WCGraph {
    struct Node {
        int v, w, c;
    };

    std::vector<std::vector<Node>> edge;
    _WCGraph() {
    }
    _WCGraph(int n) : edge(n + 1){};
    void add(int u, int v, int w, int c) {
        edge[u].emplace_back(Node{v, w, c});
    }
};
struct Graph : public _WGraph {
    void add_two(int u, int v, int w) {
        add(u, v, w);
        add(v, u, 0);
    }
};

} // namespace _Graph_edge
