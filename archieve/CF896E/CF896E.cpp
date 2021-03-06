#include <iostream>
using namespace std;
namespace IO {
int x;
int read() {
    x      = 0;
    char c = getchar(), f = 0;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = 1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    x = (f ? -x : x);
    return x;
}
} // namespace IO
using IO::read;
const int N          = 110005;
const int block_size = 348;
int n, m;
int a[N];
int belong[N], tag[N], mmax[N];
int L(int x) {
    return x * block_size - block_size + 1;
}
int R(int x) {
    return x * block_size;
}
struct Field {
    int rt, cnt;
} f[400 + 5][N];
int fa[N], v[N];
int lb[400 + 5], rb[400 + 5];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void push(int x) {
    for (int i = lb[x]; i <= rb[x]; i++) {
        a[i]           = v[find(i)];
        f[x][a[i]].cnt = f[x][a[i]].rt = 0;
        a[i] -= tag[x];
    }
    tag[x] = 0;
    for (int i = lb[x]; i <= rb[x]; i++) {
        fa[i] = 0;
    }
}
void init(int x) {
    mmax[x] = 0;
    for (int i = lb[x]; i <= rb[x]; i++) {
        mmax[x] = max(mmax[x], a[i]);
        f[x][a[i]].cnt++;
        if (f[x][a[i]].rt) {
            fa[i] = f[x][a[i]].rt;
        } else {
            v[i]          = a[i];
            fa[i]         = i;
            f[x][a[i]].rt = i;
        }
    }
}
void merge(int x, int a, int b) {
    Field &s = f[x][a], &t = f[x][b];
    if (t.rt) {
        fa[s.rt] = t.rt;
    } else {
        t.rt    = s.rt;
        v[s.rt] = b;
    }
    t.cnt += s.cnt;
    s.cnt = s.rt = 0;
}
void addtag(int x, int t) {
    if (t <= mmax[x] - tag[x] - t) {
        for (int i = tag[x] + 1; i <= tag[x] + t; ++i) {
            if (f[x][i].rt) {
                merge(x, i, i + t);
            }
        }
        tag[x] += t;
    } else {
        for (int i = mmax[x]; i > tag[x] + t; i--) {
            if (f[x][i].rt) {
                merge(x, i, i - t);
            }
        }
        mmax[x] = min(mmax[x], tag[x] + t);
    }
}
void change(int l, int r, int x) {
    int p = belong[l], q = belong[r];
    push(p);
    if (p != q)
        push(q);
    if (p != q) {
        for (int i = l; i <= rb[p]; i++) {
            if (a[i] > x) {
                a[i] -= x;
            }
        }
        for (int i = lb[q]; i <= r; i++) {
            if (a[i] > x) {
                a[i] -= x;
            }
        }
        for (int i = p + 1; i <= q - 1; i++) {
            addtag(i, x);
        }
        init(p);
        init(q);
    } else {
        for (int i = l; i <= r; i++) {
            if (a[i] > x) {
                a[i] -= x;
            }
        }
        init(p);
    }
}
int query(int l, int r, int x) {
    int p = belong[l], q = belong[r], res = 0;
    if (p != q) {
        for (int i = l; i <= rb[p]; i++) {
            if (v[find(i)] - tag[p] == x) {
                res++;
            }
        }
        for (int i = lb[q]; i <= r; i++) {
            if (v[find(i)] - tag[q] == x) {
                res++;
            }
        }
        for (int i = p + 1; i <= q - 1; i++) {
            if (x + tag[i] <= 100000) {
                res += f[i][x + tag[i]].cnt;
            }
        }
    } else {
        for (int i = l; i <= r; i++) {
            if (v[find(i)] - tag[p] == x) {
                res++;
            }
        }
    }
    return res;
}
int main() {
    n = read();
    m = read();
    for (int i = 1; i <= n; i++) {
        a[i]      = read();
        belong[i] = (i - 1) / block_size + 1;
    }
    for (int i = belong[1]; i <= belong[n]; i++) {
        lb[i] = L(i);
        rb[i] = R(i);
        init(i);
        tag[i] = 0;
    }
    while (m--) {
        int op = read(), l = read(), r = read(), x = read();
        if (op == 1) {
            change(l, r, x);
        } else {
            printf("%d\n", query(l, r, x));
        }
    }
    return 0;
}