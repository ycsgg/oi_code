#include <iostream>
#include <unordered_map>
using namespace std;
typedef long long ll;
const ll mod = 1e7 + 19;
struct Op {
    int typ, pos, val;
} op[100005];
unordered_map<int, int> m;
istream &operator>>(istream &in, Op &a) {
    in >> a.typ;
    if (a.typ == 1) {
        in >> a.pos >> a.val;
    } else if (a.typ == 5) {
        in >> a.pos;
    } else if (a.typ == 6) {
        return in;
    } else {
        in >> a.val;
        if (a.typ == 3 && a.val == 0) {
            a.typ == 4;
        }
    }
    a.val = (a.val % mod + mod) % mod;
    return in;
}
ll addtag, multag = 1, sum;
ll inv[mod];
ll a[105], b[105];
int n, q, t;
ll getVal(int pos) {
    if (m.count(pos)) {
        return 1ll * m[pos] * multag % mod + addtag % mod;
    } else {
        return addtag % mod;
    }
}
ll ans;
void solve(int id) {
    if (op[id].typ == 1) {
        sum = (sum - getVal(op[id].pos) + mod) % mod;
        m[op[id].pos] =
            1ll * (op[id].val - addtag + mod) % mod * inv[multag] % mod;
        sum = (sum + op[id].val) % mod;
    } else if (op[id].typ == 2) {
        addtag = (addtag + op[id].val) % mod;
        sum    = (sum + 1ll * n * op[id].val) % mod;
    } else if (op[id].typ == 3) {
        multag = 1ll * multag * op[id].val % mod;
        addtag = 1ll * addtag * op[id].val % mod;
        sum    = 1ll * sum * op[id].val % mod;
    } else if (op[id].typ == 4) {
        multag = 1;
        addtag = op[id].val;
        sum    = (1ll * n * op[id].val) % mod;
        m.clear();
    } else if (op[id].typ == 5) {
        ans = (ans + getVal(op[id].pos)) % mod;
    } else {
        ans = (ans + sum) % mod;
    }
}
int main() {
    inv[1] = 1;
    for (int i = 2; i < mod; i++) {
        inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    }
    cin >> n >> q;
    for (int i = 1; i <= q; i++) {
        cin >> op[i];
    }
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= t; i++) {
        for (int j = 1; j <= q; j++) {
            solve((a[i] + j * b[i]) % q + 1);
        }
    }
    cout << ans % mod;
    return 0;
}