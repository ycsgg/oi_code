#include "highway.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;
namespace Solution {
const int N = 1e5 + 10;
struct Graph {
    struct Node {
        int v, w;
    };
    vector<Node> edge[N];
    void add(int u, int v, int w) {
        edge[u].emplace_back(Node{v, w});
    }
};
int getPath(std::vector<int> &w, ll val) {
    fill(w.begin(), w.end(), 0);
    int l = 0, r = w.size() - 1, res = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        for (int i = l; i <= mid; i++) {
            w[i] = 1;
        }
        if (ask(w) == val) {
            l = mid + 1;
        } else {
            for (int i = l; i <= mid; i++) {
                w[i] = 0;
            }
            res = mid;
            r = mid - 1;
        }
    }
    return res;
}
auto bfs(int pos, int n, const Graph &G) {
    vector<int> dis(n, -1), id(n);
    queue<int> q;
    q.push(pos);
    dis[pos] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto e : G.edge[x]) {
            auto v = e.v;
            auto w = e.w;
            if (dis[v] == -1) {
                dis[v] = dis[x] + 1;
                id[v] = w;
                q.push(v);
            }
        }
    }
    return make_pair(dis, id);
}
auto SplitGraph(std::vector<int> &disx, std::vector<int> &disy) {
    vector<int> resx, resy;
    for (int i = 0; i < disx.size(); i++) {
        if (disx[i] < disy[i]) {
            resx.push_back(i);
        } else {
            resy.push_back(i);
        }
    }
    return make_pair(resx, resy);
}
int getPos(const std::vector<int> &in, const std::vector<int> &out,
           std::vector<int> &w, const std::vector<int> &inx,
           std::vector<int> &outx, int pos, ll val) {
    int l = 0, r = in.size() - 1, res = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        fill(w.begin(), w.end(), 1);
        w[pos] = 0;
        for (auto v : out) {
            w[outx[v]] = 0;
        }
        for (int i = 1; i <= mid; i++) {
            w[inx[in[i]]] = 0;
        }
        ll ret = ask(w);
        if (ret == val) {
            r = mid - 1;
            res = mid;
        } else {
            l = mid + 1;
        }
    }
    return in[res];
}
} // namespace Solution
void find_pair(int N, std::vector<int> U, std::vector<int> V, int A, int B) {
    using namespace Solution;
    int m = U.size();
    vector<int> w(m, 0);
    Graph G;
    for (int i = 0; i < m; i++) {
        G.add(U[i], V[i], i);
        G.add(V[i], U[i], i);
    }
    auto res = ask(w);
    auto pos = getPath(w, res);
    auto [disx, idx] = bfs(U[pos], N, G);
    auto [disy, idy] = bfs(V[pos], N, G);
    auto [resx, resy] = SplitGraph(disx, disy);
    sort(resx.begin(), resx.end(), [&](const auto &x, const auto &y) -> bool {
        return disx[x] < disx[y];
    });
    sort(resy.begin(), resy.end(), [&](const auto &x, const auto &y) -> bool {
        return disy[x] < disy[y];
    });
    auto S = getPos(resx, resy, w, idx, idy, pos, res);
    auto T = getPos(resy, resx, w, idy, idx, pos, res);
    answer(S, T);
}
// Asusetic eru quionours.