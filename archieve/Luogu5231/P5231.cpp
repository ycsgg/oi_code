
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 1e7 + 5;
const int M = 105;
int n, m;
char s[N];
char t[100005][M];
int tlen[100005];
int tr[M * 100000][4];
int change(char c) {
    switch (c) {
    case 'E':
        return 0;
        break;
    case 'S':
        return 1;
    case 'W':
        return 2;
    case 'N':
        return 3;
    default:
        return 0;
    }
}
int tot;
void insert(char *s, int len) {
    int now = 0;
    for (int i = 0; i < len; i++) {
        int c = change(s[i]);
        if (!tr[now][c]) {
            tr[now][c] = ++tot;
        }
        now = tr[now][c];
    }
}
int fail[M * 100000];
void build() {
    queue<int> q;
    for (int i = 0; i < 4; i++) {
        if (tr[0][i]) {
            q.push(tr[0][i]);
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            if (tr[x][i]) {
                fail[tr[x][i]] = tr[fail[x]][i];
                q.push(tr[x][i]);
            } else {
                tr[x][i] = tr[fail[x]][i];
            }
        }
    }
}
bool pos[M * 100000];
int solve(char *s, int len) {
    int now = 0, ans = 0;
    for (int i = 0; i < len; i++) {
        int c = change(s[i]);
        now   = tr[now][c];
        if (pos[now]) {
            ans = i + 1;
        }
    }
    return ans;
}
int main() {
    cin >> n >> m;
    cin >> s + 1;
    for (int i = 1; i <= m; i++) {
        cin >> t[i];
        tlen[i] = strlen(t[i]);
        insert(t[i], tlen[i]);
    }
    build();
    int now = 0;
    for (int i = 1; i <= n; i++) {
        int c = change(s[i]);
        now   = tr[now][c];
        int k = now;
        while (k && !pos[k]) {
            pos[k] = 1;
            k      = fail[k];
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << solve(t[i], tlen[i]) << endl;
    }
}


