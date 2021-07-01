#include <iostream>
#include <vector>
using namespace std;
const int N = 2e6 + 10;
struct Node {
    int ls, rs;
};
int T;
bool isleaf(int x, const vector<Node> &Tr) {
    return x != 0 && !Tr[x].ls && !Tr[x].rs;
}
vector<int> siz;
bool check(int x, const vector<Node> &Tr) {
    if (Tr[x].ls && !check(Tr[x].ls, Tr))
        return false;
    if (Tr[x].rs && !check(Tr[x].rs, Tr))
        return false;

    siz[x] = siz[Tr[x].ls] + siz[Tr[x].rs] + 1;

    if (siz[Tr[x].ls] > 1 && siz[Tr[x].rs] > 1) {
        return false;
    }

    return true;
}
int ch[N][4];
bool ok[N];
int cnt = 0, root = 0;
void merge(int &now, int x, const vector<Node> &Tr) {
    if (!now) {
        now = ++cnt;
    }
    if (isleaf(x, Tr)) {
        ok[now] = 1;
        return;
    }

    if (!Tr[x].ls) {
        merge(ch[now][0], Tr[x].rs, Tr);
    }
    if (!Tr[x].rs) {
        merge(ch[now][1], Tr[x].ls, Tr);
    }

    if (Tr[x].ls && isleaf(Tr[x].rs, Tr)) {
        merge(ch[now][2], Tr[x].ls, Tr);
    }
    if (Tr[x].rs && isleaf(Tr[x].ls, Tr)) {
        merge(ch[now][3], Tr[x].rs, Tr);
    }
}
bool check(int x) {
    if (!x)
        return false;
    if (ok[x])
        return true;
    return check(ch[x][0]) && check(ch[x][1]) && check(ch[x][2]) &&
           check(ch[x][3]);
}
void clear() {
    for (int i = 1; i <= cnt; i++) {
        ch[i][0] = ch[i][1] = ch[i][2] = ch[i][3] = 0;
        ok[i]                                     = 0;
    }
    root = 0;
    cnt  = 0;
}
int main() {
    cin >> T;
    while (T--) {
        clear();
        int m;
        cin >> m;
        for (int i = 1; i <= m; i++) {
            int n;
            cin >> n;
            siz.assign(n + 1, 0);
            vector<Node> Tr(n + 1);
            for (int j = 1; j <= n; j++) {
                cin >> Tr[j].ls >> Tr[j].rs;
            }
            if (!check(1, Tr)) {
                continue;
            }
            merge(root, 1, Tr);
        }
        if (!check(1)) {
            cout << "No" << endl;
            continue;
        }
        cout << "Almost Complete" << endl;
    }
    return 0;
}
// Asusetic eru quionours