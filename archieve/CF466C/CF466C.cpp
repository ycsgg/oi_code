#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_map>
using namespace std;
#define ll long long
const int N  = 300000 + 5;
const ll mod = 1e9 + 9;
int n, m;
struct Matrix {
    long long v[3][3];
    Matrix operator*(Matrix B) {
        Matrix Ans;
        memset(Ans.v, 0, sizeof(Ans.v));
        for (int k = 1; k <= 2; k++) {
            for (int i = 1; i <= 2; i++) {
                for (int j = 1; j <= 2; j++) {
                    Ans.v[i][j] += (this->v[i][k] * B.v[k][j] + mod) % mod;
                    Ans.v[i][j] %= mod;
                }
            }
        }
        return Ans;
    }
};
Matrix a;
Matrix f_mat[5][257];
Matrix Super_Power(Matrix A, ll b) {
    Matrix Ans;
    Ans.v[1][2] = Ans.v[2][1] = 0;
    for (int i = 1; i <= 2; i++) {
        Ans.v[i][i] = 1;
    }
    int cnt = 0;
    while (b) {
        if (b & 255) {
            Ans = Ans * f_mat[cnt][b & 255];
        }
        b >>= 8;
        ++cnt;
    }
    return Ans;
}
struct Node {
    ll v, a0, a1;
} tree[N << 2];
unordered_map<int, ll> _f;
ll fib[2000005];
ll f(int x) {
    if (x <= 2e6) {
        return fib[x - 1];
    }
    if (_f.count(x)) {
        return _f[x];
    } else {
        _f[x] = Super_Power(a, x).v[2][1];
    }
    return _f[x];
}
void pushdown(int k, int l, int r) {
    if (tree[k].a0 != 0 || tree[k].a1 != 0) {
        int mid        = (l + r) >> 1;
        tree[k * 2].a0 = (tree[k].a0 + tree[k * 2].a0) % mod;
        tree[k * 2].a1 = (tree[k].a1 + tree[k * 2].a1) % mod;
        tree[k * 2].v =
            (tree[k * 2].v + tree[k].a1 * (f(mid - l + 2) - 1) % mod +
             tree[k].a0 * f(mid - l + 1) % mod) %
            mod;
        int pos = mid - l + 2;
        tree[k * 2 + 1].a0 += f(pos - 1) * tree[k].a1 + f(pos - 2) * tree[k].a0;
        tree[k * 2 + 1].a0 %= mod;
        tree[k * 2 + 1].a1 += f(pos) * tree[k].a1 + f(pos - 1) * tree[k].a0;
        tree[k * 2 + 1].a1 %= mod;
        tree[k * 2 + 1].v +=
            tree[k].a1 * (f(r - l + 2) - 1) + tree[k].a0 * f(r - l + 1) -
            tree[k].a1 * (f(mid - l + 2) - 1) - tree[k].a0 * f(mid - l + 1);
        tree[k * 2 + 1].v %= mod;
        tree[k].a0 = 0, tree[k].a1 = 0;
    }
}
void modify(int k, int l, int r, int L, int R, int y) {
    if (l > R || r < L)
        return;
    if (l >= L && r <= R) {
        tree[k].a0 = (tree[k].a0 + f(l - L + 1 + y)) % mod;
        tree[k].a1 = (tree[k].a1 + f(l - L + 2 + y)) % mod;
        tree[k].v += f(r - l + 1) * f(l - L + 1 + y) % mod +
                     (f(r - l + 2) - 1) * f(l - L + 2 + y) % mod;
        tree[k].v %= mod;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(k, l, r);
    if (L <= mid) {
        modify(k * 2, l, mid, L, R, y);
    }
    if (mid < R) {
        modify(k * 2 + 1, mid + 1, r, L, R, y);
    }
    tree[k].v = (tree[k * 2].v + tree[k * 2 + 1].v) % mod;
    tree[k].v %= mod;
}

ll query(int k, int l, int r, int L, int R) {
    if (l > R || r < L)
        return 0;
    if (l >= L && r <= R)
        return tree[k].v;
    pushdown(k, l, r);
    int mid = (l + r) >> 1;
    ll res  = 0;
    if (L <= mid) {
        res += query(k * 2, l, mid, L, R);
        res %= mod;
    }
    if (mid < R) {
        res += query(k * 2 + 1, mid + 1, r, L, R);
        res %= mod;
    }
    return res % mod;
}
void init() {
    fib[0] = fib[1] = 1;
    for (int i = 2; i <= 2000000; i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
    }
    f_mat[0][1].v[1][1] = 0;
    f_mat[0][1].v[1][2] = 1;
    f_mat[0][1].v[2][1] = 1;
    f_mat[0][1].v[2][2] = 1;
    f_mat[0][0].v[1][1] = 1;
    f_mat[0][0].v[1][2] = 0;
    f_mat[0][0].v[2][1] = 0;
    f_mat[0][0].v[2][2] = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 2; j < 256; ++j)
            f_mat[i][j] = f_mat[i][j - 1] * f_mat[i][1];
        if (i < 3)
            f_mat[i + 1][1] = f_mat[i][255] * f_mat[i][1];
    }
}
void build(int k, int l, int r) {
    if (l == r) {
        cin >> tree[k].v;
        return;
    }
    int mid = (l + r) >> 1;
    build(k * 2, l, mid);
    build(k * 2 + 1, mid + 1, r);
    tree[k].v = tree[k * 2].v + tree[k * 2 + 1].v;
    tree[k].v %= mod;
}
int main() {
    cin >> n >> m;
    build(1, 1, n);
    init();
    for (int i = 1; i <= m; i++) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if (t == 1) {
            modify(1, 1, n, x, y, 0);
        } else {
            printf("%lld\n", (query(1, 1, n, x, y) % mod + mod) % mod);
        }
    }
    return 0;
}