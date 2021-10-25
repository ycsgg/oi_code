#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
int k;
bool vis[1000005];
int main() {
    cin >> k;
    deque<pair<int, int>> q;
    q.emplace_front(1, 1);
    vis[1] = 1;
    while (!q.empty()) {
        auto [now, val] = q.front();
        q.pop_front();
        if (now == 0) {
            cout << val << '\n';
            return 0;
        }
        if (!vis[now * 10 % k]) {
            vis[now * 10 % k] = 1;
            q.emplace_front(now * 10 % k, val);
        }
        if (!vis[now + 1]) {
            q.emplace_back(now + 1, val + 1);
        }
    }
    return 0;
}
// Asusetic eru quionours.
