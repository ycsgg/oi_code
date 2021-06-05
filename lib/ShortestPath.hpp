#pragma once
#include "Graph.hpp"
#include <queue>
namespace ShortestPath {
using Graph = _Graph_edge::Graph;
class Dijkstra {
  private:
    Dijkstra();
    struct Node {
        int v, dis;
        const bool operator<(const Node &B) const {
            return dis > B.dis;
        }
    };

  public:
    static std::vector<int> ShortestPath(const int S, const Graph &G) {
        std::vector<int> dis;
        dis.resize(G.edge.size() + 1);
        dis.assign(dis.size(), -1);
        std::priority_queue<Node> q;
        dis[S] = 0;
        q.push(Node{S, dis[S]});
        while (!q.empty()) {
            int now = q.top().v;
            for (auto e : G.edge[now]) {
                int v = e.v;
                if (dis[v] == -1 || dis[v] > dis[now] + e.w) {
                    dis[v] = dis[now] + e.w;
                    q.push(Node{v, dis[v]});
                }
            }
        }
        return dis;
    }
};
} // namespace ShortestPath
