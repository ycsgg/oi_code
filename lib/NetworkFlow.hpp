#pragma once
#include "Graph.hpp"
#include <queue>
namespace NetworkFlow {
using Graph = _Graph_nxt::Graph;
class Dinic {
  private:
    Dinic();
    const static int INF = 0x3f3f3f3f;

  public:
    static int MaxFlow(const int S, const int T, Graph &G) {
        std::vector<int> level;
        std::vector<int> cur;
        static auto bfs = [&](const int S, const int T) -> bool {
            level.assign(G.head.size() + 1, 0);
            level[S] = 1;
            std::queue<int> q;
            q.push(S);
            while (!q.empty()) {
                int now = q.front();
                q.pop();
                for (int i = G.head[now]; ~i; i = G.edge[i].nxt) {
                    int v = G.edge[i].v;
                    if (!level[v] && G.edge[i].w) {
                        level[v] = level[now] + 1;
                        q.push(v);
                    }
                }
            }
            return level[T];
        };
        static auto dfs = [&](auto self, int x, const int T, int maxflow,
                              Graph &G) -> int {
            if (x == T) {
                return maxflow;
            }
            int res = 0;
            for (int &i = cur[x]; ~i && res < maxflow; i = G.edge[i].nxt) {
                int v = G.edge[i].v;
                if (G.edge[i].w && level[v] == level[x] + 1) {
                    int x = self(self, v, T,
                                 std::min(G.edge[i].w, maxflow - res), G);
                    if (x) {
                        G.edge[i].w -= x;
                        G.edge[i ^ 1].w += x;
                        res += x;
                    }
                }
            }
            if (res < maxflow) {
                level[x] = -1;
            }
            return res;
        };
        Graph tmpG = G;
        int res    = 0;
        while (bfs(S, T)) {
            cur.assign(G.head.begin(), G.head.end());
            int x;
            while (x = dfs(dfs, S, T, INF, G)) {
                res += x;
            }
        }
        return res;
    }
};
} // namespace NetworkFlow
