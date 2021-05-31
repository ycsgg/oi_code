#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 5;
int n, q;
string s[N];
int opt[N];
struct Query {
    string ip;
    int id;
} qr[N];
namespace Trie {
int rt = 0;
int ch[N * 32][2];
int tag[N * 32], val[N * 32];
int end[N * 32];
int cnt;
void add(int x, int v) {
    tag[x] += v;
    val[x] += v;
}
void pushdown(int x) {
    if (tag[x] == 0) {
        return;
    }
    if (ch[x][0] && !end[ch[x][0]]) {
        add(ch[x][0], tag[x]);
    }
    if (ch[x][1] && !end[ch[x][1]]) {
        add(ch[x][1], tag[x]);
    }
    tag[x] = 0;
}
void update(string s, int v) {
    int now = rt;
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (!ch[now][s[i] - '0']) {
            ch[now][s[i] - '0'] = ++cnt;
        }
        pushdown(now);
        now = ch[now][s[i] - '0'];
    }
    end[now] += v;
    tag[now]++;
    val[now]++;
}
int query(string s) {
    int len = s.length();
    int now = rt;
    for (int i = 0; i < len; i++) {
        if (!ch[now][s[i] - '0']) {
            ch[now][s[i] - '0'] = ++cnt;
        }
        pushdown(now);
        now = ch[now][s[i] - '0'];
    }
    return val[now];
}
} // namespace Trie
vector<int> del[N], add[N];
int ans[N];
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        static char op[4];
        cin >> op >> s[i];
        if (op[0] == 'A') {
            opt[i] = 1;
        } else {
            opt[i] = -1;
        }
    }
    for (int i = 1; i <= q; i++) {
        cin >> qr[i].ip;
        qr[i].id = i;
        int l, r;
        cin >> l >> r;
        del[l].push_back(i);
        add[r].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        Trie::update(s[i], opt[i]);
        for (auto tmp : del[i]) {
            ans[qr[tmp].id] -= Trie::query(qr[tmp].ip);
        }
        for (auto tmp : add[i]) {
            ans[qr[tmp].id] += Trie::query(qr[tmp].ip);
        }
    }
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
// Asusetic eru quionours