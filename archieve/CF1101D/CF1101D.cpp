#include <iostream>
#include <random>
using namespace std;
namespace DoNotUsePollardRhoPlz {
typedef long long ll;
ll max_factor;
ll gcd(ll a, ll b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

ll qpow(ll x, ll p, ll mod) {
    ll ans = 1;
    while (p) {
        if (p & 1)
            ans = ans * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return ans;
}

bool mr(ll x, ll b) {
    ll k = x - 1;
    while (k) {
        ll cur = qpow(b, k, x);
        if (cur != 1 && cur != x - 1)
            return false;
        if ((k & 1) == 1 || cur == x - 1)
            return true;
        k >>= 1;
    }
    return true;
}

bool prime(ll x) {
    if (x < 2)
        return false;
    if (x == 2 || x == 3 || x == 7 || x == 61 || x == 24251)
        return true;
    return mr(x, 2) && mr(x, 61);
}

ll sq_add(ll x, ll c, ll mod) {
    return (x * x + c) % mod;
}

ll PollardRho(ll x) {
    ll s = 0, t = 0, c = 1ll * rand() % (x - 1) + 1;
    int step = 0, goal = 1;
    ll val = 1;
    while ("qwq") {
        for (step = 1; step <= goal; ++step) {
            t   = sq_add(t, c, x);
            val = (ll)val * abs(t - s) % x;
            if ((step % 127) == 0) {
                ll d = gcd(val, x);
                if (d > 1)
                    return d;
            }
        }
        ll d = gcd(val, x);
        if (d > 1)
            return d;
        goal *= 2;
        s   = t;
        val = 1;
    }
}

void fac(ll x) {
    if (x <= max_factor || x < 2)
        return;
    if (prime(x)) {
        max_factor = max_factor > x ? max_factor : x;
        return;
    }
    ll p = x;
    while (p >= x)
        p = PollardRho(x);
    while ((x % p) == 0)
        x /= p;
    fac(x);
    fac(p);
}
} // namespace DoNotUsePollardRhoPlz

const int N = 2e5 + 10;
const int M = 600000;
typedef long long ll;
int a[N];
int ans;
int n;
int factor[N][15], dis[N][15];
struct Edge {
    int v;
    int nxt;
} edge[400005];
int head[400005], ecnt;
void add(int x, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[x];
    head[x]        = ecnt;
}
int prime[M + 10], pcnt, mindiv[M + 10];
bool vis[M + 10];
void init() {
    for (int i = 2; i <= M; i++) {
        if (!vis[i]) {
            prime[++pcnt] = i;
            mindiv[i]     = i;
        }
        for (int j = 1; j <= pcnt; j++) {
            if (i * prime[j] > M) {
                break;
            }
            vis[i * prime[j]]    = 1;
            mindiv[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
void dfs(int x, int fa) {
    for (int i = head[x]; i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa)
            continue;
        dfs(v, x);
        for (int j = 1; j <= factor[x][0]; j++) {
            for (int k = 1; k <= factor[v][0]; k++) {
                if (factor[x][j] == factor[v][k]) {
                    ans       = max(ans, dis[x][j] + dis[v][k] + 1);
                    dis[x][j] = max(dis[x][j], dis[v][k] + 1);
                }
            }
        }
    }
}
int tmp[20];
void dFac(int x, int id) {
    if (x == 1) {
        return;
    }
    tmp[0] = 0;
    while (x != 1) {
        if (x <= M)
            break;
        DoNotUsePollardRhoPlz::max_factor = 0;
        DoNotUsePollardRhoPlz::fac(x);
        int d         = DoNotUsePollardRhoPlz::max_factor;
        tmp[++tmp[0]] = d;
        x /= d;
        while (x % d == 0) {
            x /= d;
        }
    }
    while (x != 1) {
        int d                       = mindiv[x];
        factor[id][++factor[id][0]] = d;
        while (x % d == 0) {
            x /= d;
        }
    }
    if (x != 1)
        factor[id][++factor[id][0]] = x;
    for (int x = tmp[0]; x >= 1; x--) {
        factor[id][++factor[id][0]] = tmp[x];
    }
}
int main() {
    init();
    cin >> n;
    bool flag = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] != 1) {
            flag = 1;
        }
    }
    if (!flag) {
        cout << 0;
        return 0;
    }
    for (int i = 1; i < n; i++) {
        int x, v;
        cin >> x >> v;
        add(x, v);
        add(v, x);
    }
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        dFac(x, i);
    }
    dfs(1, 0);
    cout << ans + 1;
}