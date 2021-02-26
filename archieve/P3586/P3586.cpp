
#include <iostream>
using namespace std;
#include<cstdio>
#ifdef DEBUG
#define Err(a) std::cerr << " >>| " << (a) << endl
#else
#define Err(a)
#endif
const int N       = 1e6 + 10;
const int MAXNODE = N << 5;
int n, m;
int lson[MAXNODE], rson[MAXNODE], siz[MAXNODE], cnt;
long long val[MAXNODE];
void update(int &rt, int l, int r, int d, int dcnt) {
    if (!rt) {
        rt = ++cnt;
    }
    if (l == r) {
        siz[rt] += dcnt;
        val[rt] += dcnt * l;
        return;
    }
    int mid = (l + r) / 2;
    if (d <= mid) {
        update(lson[rt], l, mid, d, dcnt);
    } else {
        update(rson[rt], mid + 1, r, d, dcnt);
    }
    siz[rt] = siz[lson[rt]] + siz[rson[rt]];
    val[rt] = val[lson[rt]] + val[rson[rt]];
}
long long queryval(int rt, int l, int r, int L, int R) {
    if (!rt || l > R || r < L)
        return 0ll;
    if (L <= l && R >= r) {
        return val[rt];
    }
    int mid = (l + r) / 2;
    return queryval(lson[rt], l, mid, L, R) +
           queryval(rson[rt], mid + 1, r, L, R);
}
int querysiz(int rt, int l, int r, int L, int R) {
    if (!rt || l > R || r < L)
        return 0ll;
    if (L <= l && R >= r) {
        return siz[rt];
    }
    int mid = (l + r) / 2;
    return querysiz(lson[rt], l, mid, L, R) +
           querysiz(rson[rt], mid + 1, r, L, R);
}
int root, max_left = 1e9 + 5;
int a[N];
signed main() {
    cin >> n >> m;
    update(root, 0, max_left, 0, n);
    Err("Pass1");
    while (m--) {
        char op[5];
        int k, s;
        scanf("%s%d%d", op, &k, &s);
        if (op[0] == 'U') {
            update(root, 0, max_left, a[k], -1);
            a[k] = s;
            Err(k);
            Err(a[k]);
            update(root, 0, max_left, s, 1);
        } else {
            int x         = querysiz(root, 0, max_left, s, max_left);
            long long sum = queryval(root, 0, max_left, 0, s - 1);
            if (sum >= (k - x) * 1ll * s) {
                // cout << "TAK" << endl;
                puts("TAK");
            } else {
                puts("NIE");
                // cout << "NIE" << endl;
            }
        }
    }
}


