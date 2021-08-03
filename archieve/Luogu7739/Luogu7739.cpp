#include <array>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
const ll mod = 998244353;
struct Matrix {
    int a[2][2];
    int *operator[](const int x) {
        return a[x];
    }
    const int *operator[](const int x) const {
        return a[x];
    }
    friend ostream &operator<<(ostream &out, const Matrix &A) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                out << A[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }
    Matrix operator*(const Matrix &b) const {
        Matrix res;
        // cout << *this << endl << b << endl;
        res[0][0] =
            (1ll * a[0][0] * b[0][0] % mod + 1ll * a[0][1] * b[1][0] % mod) %
            mod;
        res[0][1] =
            (1ll * a[0][0] * b[0][1] % mod + 1ll * a[0][1] * b[1][1] % mod) %
            mod;
        res[1][0] =
            (1ll * a[1][0] * b[0][0] % mod + 1ll * a[1][1] * b[1][0] % mod) %
            mod;
        res[1][1] =
            (1ll * a[1][0] * b[0][1] % mod + 1ll * a[1][1] * b[1][1] % mod) %
            mod;
        return res;
    }
} W, E, Init, Base;
void init() {
    Init[0][0] = Init[1][1] = 1;
    W[0][0] = 1;
    W[0][1] = 1;
    W[1][1] = 1;
    E[0][0] = 2;
    E[0][1] = mod - 1;
    E[1][0] = 1;
    Base = Init;
    Base[0][1] = 1;
}
int n, m;
char s[N];
namespace Splay {
struct Splay {
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
    int ch[N][2], fa[N], siz[N];
    int trans[N], rev[N];
    int root, tot;
    Matrix sum[N][4], val[N][2];
    void init() {
        tot = 2;
        ch[1][1] = 2;
        fa[2] = 1;
        root = 1;
        siz[2] = 1;
        siz[1] = 2;
        for (int i = 0; i < 3; i++) {
            sum[i][0] = sum[i][1] = sum[i][2] = sum[i][3] = Init;
            val[i][0] = val[i][1] = Init;
        }
    }
    void pushup(int x) {
        sum[x][0] = sum[rs(x)][0] * val[x][0] * sum[ls(x)][0];
        sum[x][2] = sum[rs(x)][2] * val[x][1] * sum[ls(x)][2];
        sum[x][1] = sum[ls(x)][1] * val[x][0] * sum[rs(x)][1];
        sum[x][3] = sum[ls(x)][3] * val[x][1] * sum[rs(x)][3];
        siz[x] = siz[ls(x)] + siz[rs(x)] + 1;
    }
    void pushdown(int x) {
        if (trans[x]) {
            swap(sum[ls(x)][0], sum[ls(x)][2]);
            swap(sum[ls(x)][1], sum[ls(x)][3]);
            swap(val[ls(x)][0], val[ls(x)][1]);
            trans[ls(x)] ^= 1;
            swap(sum[rs(x)][0], sum[rs(x)][2]);
            swap(sum[rs(x)][1], sum[rs(x)][3]);
            swap(val[rs(x)][0], val[rs(x)][1]);
            trans[rs(x)] ^= 1;
            trans[x] = 0;
        }
        if (rev[x]) {
            swap(sum[ls(x)][0], sum[ls(x)][1]);
            swap(sum[ls(x)][2], sum[ls(x)][3]);
            swap(ch[ls(x)][0], ch[ls(x)][1]);
            rev[ls(x)] ^= 1;
            swap(sum[rs(x)][0], sum[rs(x)][1]);
            swap(sum[rs(x)][2], sum[rs(x)][3]);
            swap(ch[rs(x)][0], ch[rs(x)][1]);
            rev[rs(x)] ^= 1;
            rev[x] = 0;
        }
    }
    bool identity(const int &x) {
        return rs(fa[x]) == x;
    }
    void rotate(const int &x) {
        int y = fa[x], z = fa[y];
        int k = identity(x);
        if (z) {
            ch[z][identity(y)] = x;
        }
        ch[y][k] = ch[x][k ^ 1];
        ch[x][k ^ 1] = y;
        fa[ch[y][k]] = y;
        fa[y] = x;
        fa[x] = z;
        pushup(y);
    }
    void splay(int x, int goal) {
        if (!goal) {
            root = x;
        }
        while (fa[x] != goal) {
            int y = fa[x];
            if (fa[y] != goal) {
                rotate(identity(y) ^ identity(x) ? x : y);
            }
            rotate(x);
        }
        pushup(x);
    }
    void find(int kth, int goal) {
        int x = root;
        while (siz[ls(x)] + 1 != kth) {
            pushdown(x);
            if (siz[ls(x)] >= kth) {
                x = ls(x);
            } else {
                kth -= siz[ls(x)] + 1;
                x = rs(x);
            }
        }
        pushdown(x);
        splay(x, goal);
    }
    void split(int x, int y) {
        find(x, 0);
        find(y + 2, root);
    }
    void build(int &x, int l, int r) {
        if (l > r)
            return;
        int mid = (l + r) / 2;
        x = ++tot;
        if (mid <= n) {
            if (s[mid] == 'W') {
                val[x][0] = W;
                val[x][1] = E;
            } else {
                val[x][0] = E;
                val[x][1] = W;
            }
        } else {
            val[x][0] = val[x][1] = Init;
        }
        if (l == r) {
            siz[x] = 1;
            sum[x][0] = sum[x][1] = val[x][0];
            sum[x][2] = sum[x][3] = val[x][1];
            return;
        }
        build(ls(x), l, mid - 1);
        build(rs(x), mid + 1, r);
        if (ls(x)) {
            fa[ls(x)] = x;
        }
        if (rs(x)) {
            fa[rs(x)] = x;
        }
        pushup(x);
        return;
    }
    void build(int lim) {
        build(ch[2][0], 1, lim);
        fa[ch[2][0]] = 2;
        pushup(2);
        pushup(1);
    }
    void append(int x, int typ) {
        find(x + 1, 0);
        x = root;
        if (typ) {
            val[x][0] = E;
            val[x][1] = W;
        } else {
            val[x][0] = W;
            val[x][1] = E;
        }
        pushup(x);
    }
    void flip(int x, int l, int r) {
        split(l, r);
        x = ls(rs(root));
        trans[x] ^= 1;
        swap(sum[x][0], sum[x][2]);
        swap(sum[x][1], sum[x][3]);
        swap(val[x][0], val[x][1]);
        pushup(fa[x]);
        pushup(root);
    }
    void reverse(int x, int l, int r) {
        split(l, r);
        x = ls(rs(root));
        rev[x] ^= 1;
        swap(sum[x][0], sum[x][1]);
        swap(sum[x][2], sum[x][3]);
        swap(ch[x][0], ch[x][1]);
        pushup(fa[x]);
        pushup(root);
    }
#undef ls
#undef rs
};
} // namespace Splay
Splay::Splay tr;
pair<int, int> get() {
    int up, down;
    auto ans = tr.sum[tr.root][0] * Base;
    up = ans[0][0];
    down = ans[0][1];
    return make_pair(up, down);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init();
    tr.init();
    cin >> n >> m >> (s + 1);
    tr.build(n + m);
    auto [x, y] = get();
    cout << x << " " << y << '\n';
    while (m--) {
        char s[10];
        cin >> s;
        if (s[0] == 'A') {
            char c;
            cin >> c;
            if (c == 'E') {
                tr.append(++n, 1);
            } else {
                tr.append(++n, 0);
            }
        } else if (s[0] == 'F') {
            int l, r;
            cin >> l >> r;
            tr.flip(1, l, r);
        } else {
            int l, r;
            cin >> l >> r;
            tr.reverse(1, l, r);
        }
        auto [x, y] = get();
        cout << x << " " << y << '\n';
    }
    cout.flush();
    return 0;
}
// Asusetic eru quionours