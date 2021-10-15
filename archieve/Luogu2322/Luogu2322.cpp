#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;
const int N = 12;
namespace ACM {
int tot, ch[N * 60][26];
int S[N * 60], fail[N * 60];
void insert(char *s, int n, int id) {
    int now = 0;
    for (int i = 1; i <= n; i++) {
        int c = s[i] - 'A';
        if (!ch[now][c]) {
            ch[now][c] = ++tot;
        }
        now = ch[now][c];
    }
    S[now] |= (1 << id - 1);
}
void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (ch[0][i]) {
            q.push(ch[0][i]);
        }
    }
    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (ch[now][i]) {
                fail[ch[now][i]] = ch[fail[now]][i];
                S[ch[now][i]] |= S[ch[fail[now]][i]];
                q.push(ch[now][i]);
            } else {
                ch[now][i] = ch[fail[now]][i];
            }
        }
    }
}
} // namespace ACM

int n;
char s[55];
char c[N * 60], path[N * 60 * (1 << 12)];
int pre[N * 60 * (1 << 12)];
bool vis[N * 60][1 << N];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> (s + 1);
        int n = strlen(s + 1);
        ACM::insert(s, n, i);
    }
    ACM::build();
    queue<tuple<int, int, int>> q;
    q.push({0, 0, 0});
    vis[0][0] = 1;
    while (!q.empty()) {
        auto [now, state, id] = q.front();
        // cout << now << " " << state << '\n';
        q.pop();
        if (state == (1 << n) - 1) {
            int cnt = 0;
            while (id) {
                c[++cnt] = path[id] + 'A';
                id = pre[id];
            }
            for (int i = cnt; i >= 1; i--) {
                cout << c[i];
            }
            return 0;
        }
        using namespace ACM;
        for (int i = 0; i < 26; i++) {
            if (!vis[ch[now][i]][state | S[ch[now][i]]]) {
                vis[ch[now][i]][state | S[ch[now][i]]] = 1;
                q.push({ch[now][i], state | S[ch[now][i]], ++tot});
                pre[tot] = id;
                path[tot] = i;
            }
        }
    }
    return 0;
}
// Asusetic eru quionours.