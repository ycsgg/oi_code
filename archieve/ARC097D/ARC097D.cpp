#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
struct Graph {
    vector<int> edge[N];
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
    vector<int> &operator[](const int &x) {
        return edge[x];
    }
    const vector<int> &operator[](const int &x) const {
        return edge[x];
    }
} Tr, STr;
int n, rt;
int siz[N], sum;
char s[N];
void pre_dfs(int x, int pre) {
    siz[x] = (s[x] == 'W');
    for (auto v : Tr[x]) {
        if (v == pre) {
            continue;
        }
        pre_dfs(v, x);
        siz[x] += siz[v];
        if (siz[v] != sum && siz[v]) {
            STr.add(x, v);
            STr.add(v, x);
        }
    }
}
int cnt[N];
void dfs(int x, int pre) {
    sum += 2;
    cnt[x] = 0;
    if (s[x] == 'W' && STr[x].size() % 2 == 0) {
        sum += 1;
        cnt[x] = 2;
    }
    if (s[x] == 'B' && STr[x].size() % 2 == 1) {
        sum += 1;
        cnt[x] = 2;
    }
    for (auto v : STr[x]) {
        if (v == pre) {
            continue;
        }
        dfs(v, x);
    }
}
int dp[N], summax;
void solve(int x, int pre) {
    dp[x] = cnt[x];
    int mmax = 0, secmax = 0;
    for (auto v : STr[x]) {
        if (v == pre) {
            continue;
        }
        solve(v, x);
        if (dp[v] > mmax) {
            secmax = mmax;
            mmax = dp[v];
        } else if (dp[v] > secmax) {
            secmax = dp[v];
        }
    }
    summax = max(summax, mmax + secmax + cnt[x]);
    dp[x] += mmax;
}
int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        Tr.add(u, v);
        Tr.add(v, u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        sum += (s[i] == 'W');
        if (s[i] == 'W') {
            rt = i;
        }
    }
    if (sum == 0) {
        cout << 0 << '\n';
        return 0;
    } else if (sum == 1) {
        cout << 1 << '\n';
        return 0;
    }
    pre_dfs(1, 0);
    sum = 0;
    dfs(rt, 0);
    solve(rt, 0);
    cout << sum - summax - 2 << '\n';
    return 0;
}
// Asusetic eru quionours.