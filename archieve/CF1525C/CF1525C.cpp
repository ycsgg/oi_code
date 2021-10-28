#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct Node {
    char c;
    int pos;
    int id;
};
void solve(vector<Node> &seq, vector<int> &res, int m) {
    int n = seq.size();
    vector<int> match(seq.size(), -1);
    vector<int> st;
    vector<Node> remain;
    for (int i = 0; i < seq.size(); i++) {
        auto p = seq[i];
        if (p.c == 'R') {
            st.push_back(i);
        }
        if (p.c == 'L') {
            if (st.empty()) {
                seq[i].pos = -seq[i].pos;
                seq[i].c = 'R';
                st.push_back(i);
            } else {
                match[st.back()] = i;
                match[i] = st.back();
                st.pop_back();
            }
        }
    }
    for (int i = 0; i < match.size(); i++) {
        auto p = match[i];
        if (p != -1) {
            res[seq[p].id] = abs(seq[p].pos - seq[i].pos) / 2;
        }
    }
    if (st.empty()) {
        return;
    }
    if (st.size() & 1) {
        for (int i = 0; i < st.size() - 1; i++) {
            st[i] = st[i + 1];
        }
        st.pop_back();
    }
    for (int i = 1; i < st.size(); i += 2) {
        seq[st[i]].pos = 2 * m - seq[st[i]].pos;
    }
    for (int i = 0; i < st.size(); i += 2) {
        res[seq[st[i]].id] = res[seq[st[i + 1]].id] =
            (seq[st[i + 1]].pos - seq[st[i]].pos) / 2;
    }
}
int main() {
    int _;
    cin >> _;
    while (_--) {
        int n, m;
        cin >> n >> m;
        vector<int> pos(n);
        vector<Node> typ(n);
        vector<Node> seq[2];
        seq[0].reserve(n);
        seq[1].reserve(n);
        for (auto &v : pos) {
            cin >> v;
        }
        for (int i = 0; i < n; i++) {
            char c;
            cin >> c;
            typ[i].id = i;
            typ[i].c = c;
            typ[i].pos = pos[i];
        }
        sort(typ.begin(), typ.end(), [&](const auto &A, const auto &B) -> bool {
            return A.pos < B.pos;
        });
        for (auto p : typ) {
            seq[p.pos & 1].push_back(p);
        }
        vector<int> ans(n, -1);
        solve(seq[0], ans, m);
        solve(seq[1], ans, m);
        for (auto v : ans) {
            cout << v << ' ';
        }
        cout << '\n';
    }
    return 0;
}
// Asusetic eru quionours.