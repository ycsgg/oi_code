### P2292 [HNOI2004]L语言

https://www.luogu.com.cn/problem/P2292

本来想用AC自动机来着.....

建一颗trie树，然后t串在上面匹配，匹配到结束节点就打个标记

需要记忆化一下，复杂度貌似略假

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;
const int N = 10005;
int n, m;
int tr[N][26], tot;
int endpos[N];
map<string, int> vis;
char s[2000006];
void insert(char *s) {
    int len = strlen(s);
    int now = 0;
    for (int i = 0; i < len; i++) {
        int c = s[i] - 'a';
        if (!tr[now][c]) {
            tr[now][c] = ++tot;
        }
        now = tr[now][c];
    }
    endpos[now] = 1;
}
bool f[2000006];
int query(char *s) {
    int ans = 0;
    int len = strlen(s + 1);
    memset(f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 0; i <= len; i++) {
        if (!f[i])
            continue;
        else
            ans = i;
        int now = 0;
        for (int j = i + 1; j <= len; j++) {
            int c = s[j] - 'a';
            if (!tr[now][c]) {
                break;
            }
            now = tr[now][c];
            if (endpos[now]) {
                f[j] = 1;
            }
        }
    }
    return ans;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        char ms[12];
        scanf("%s", ms);
        insert(ms);
    }
    while (m--) {
        scanf("%s", s + 1);
        if (vis[s + 1]) {
            cout << vis[s + 1] << endl;
        } else {
            vis[s + 1] = query(s);
            cout << vis[s + 1] << endl;
        }
    }
}
```

