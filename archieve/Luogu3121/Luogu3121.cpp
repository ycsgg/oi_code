#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 100007;
namespace AC {
int ch[N][26], fail[N], len[N], cnt;
void insert(char *s) {
    int slen = strlen(s);
    int now = 0;
    for (int i = 0; i < slen; i++) {
        int c = s[i] - 'a';
        if (!ch[now][c]) {
            ch[now][c] = ++cnt;
        }
        now = ch[now][c];
    }
    len[now] = slen;
}
void build() {
    queue<int> q;
    for (int i = 0; i < 26; ++i) {
        if (ch[0][i]) {
            q.push(ch[0][i]);
            fail[ch[0][i]] = 0;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i) {
            if (ch[u][i]) {
                fail[ch[u][i]] = ch[fail[u]][i];
                q.push(ch[u][i]);
            } else {
                ch[u][i] = ch[fail[u]][i];
            }
        }
    }
}
} // namespace AC
int n, top, loc[N], ans[N];
char p[N], s[N];
int main() {
    scanf("%s", s);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        cin >> p;
        AC::insert(p);
    }
    AC::build();
    int slen = strlen(s), now = 0;
    for (int i = 0; i < slen; ++i) {
        loc[i] = now = AC::ch[now][s[i] - 'a'];
        ans[++top]   = i;
        if (AC::len[now]) {
            top -= AC::len[now];
            now = loc[ans[top]];
        }
    }
    for (int i = 1; i <= top; ++i) {
        cout << s[ans[i]];
    }
    return 0;
}
// Asusetic eru quionours