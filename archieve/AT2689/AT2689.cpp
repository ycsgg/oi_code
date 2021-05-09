#include <iostream>
#include <vector>
using namespace std;
const int N = 1e7 + 10;
struct Edge {
    int v;
    int nxt;
} edge[200005];
int head[N], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int n;
bool a[N];
vector<int> odds, evens;
int mmax;
int prime[2000006], pcnt;
bool vis[N];
void getprime() {
    for (int i = 2; i <= mmax; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > mmax) {
                break;
            }
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int link[N];
bool match(int x) {
    for (int i = head[x]; i; i = edge[i].nxt) {
        if (!vis[edge[i].v]) {
            vis[edge[i].v] = 1;
            if (!link[edge[i].v] || match(link[edge[i].v])) {
                link[edge[i].v] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x] = 1;
        mmax = max(mmax, x + 1);
    }
    for (int i = mmax; i >= 1; i--) {
        a[i] ^= a[i - 1];
    }
    for (int i = 1; i <= mmax; i++) {
        if (a[i]) {
            if (i & 1) {
                odds.push_back(i);
            } else {
                evens.push_back(i);
            }
        }
    }
    vis[1] = 1;
    getprime();
    for (auto odd : odds) {
        for (auto even : evens) {
            if (!vis[abs(even - odd)]) {
                add(odd, even);
            }
        }
    }
    int ans = 0;
    for (auto odd : odds) {
        if (!link[odd]) {
            for (auto even : evens) {
                vis[even] = 0;
            }
            ans += match(odd);
        }
    }
    int p = ans;
    if ((odds.size() - p) & 1) {
        ans += (odds.size() - p) - 1;
    } else {
        ans += (odds.size() - p);
    }
    if ((evens.size() - p) & 1) {
        ans += (evens.size() - p) - 1;
    } else {
        ans += (evens.size() - p);
    }
    if ((odds.size() - p) & 1) {
        cout << ans + 3;
    } else {
        cout << ans;
    }
    return 0;
}
// Asusetic eru quionours