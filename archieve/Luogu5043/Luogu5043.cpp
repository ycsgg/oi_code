#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef unsigned long long ull;
const ull base = 2333;
const int N    = 505 * 2;
struct Edge {
    int v;
    int nxt;
} edge[N * 2];
int head[N], ecnt;
ull ans[N][N];
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
ull Hash(int x, int f) {
    ull q[N], ans = N, top = 0;
    for (int i = head[x]; i; i = edge[i].nxt) {
        if (edge[i].v != f) {
            q[++top] = Hash(edge[i].v, x);
        }
    }
    sort(q + 1, q + 1 + top);
    for (int i = 1; i <= top; i++) {
        ans = ans * base + q[i];
    }
    return ans * 2333 + N + 1;
}
int m, n;
int main() {
    cin >> m;
    for (int i = 1; i <= m; i++) {
        ecnt = 0;
        memset(head, 0, sizeof(head));
        cin >> n;
        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            if (x != 0) {
                add(x, j);
                add(j, x);
            }
        }
        for (int j = 1; j <= n; j++) {
            ans[i][j] = Hash(j, 0);
        }
        sort(ans[i] + 1, ans[i] + 1 + n);
        for (int j = 1, k = 0; j <= i; j++) {
            while (k <= n) {
                if (ans[i][++k] != ans[j][k]) {
                    break;
                }
            }
            if (k > n) {
                cout << j << endl;
                break;
            }
        }
    }
    return 0;
}