
#include <iostream>
using namespace std;
typedef unsigned long long ull;
const int N = 2e5 + 5;
const ull base = 23;
ull Hasha, dpow[N], sum;
int n, m;
int a[N], b[N];
int pos[N], ans;
struct Node {
  ull tot, val;
} tr[N * 4];
void pushup(int x) {
  tr[x].tot = tr[x * 2].tot + tr[x * 2 + 1].tot;
  tr[x].val = tr[x * 2].val * dpow[tr[x * 2 + 1].tot] + tr[x * 2 + 1].val;
}
void update(int x, int l, int r, int pos, int k) {
  if (l == r) {
    if (k == 0) {
      tr[x].tot -= 1;
    } else {
      tr[x].tot += 1;
    }
    tr[x].val = k;
    return;
  }
  int mid = (l + r) / 2;
  if (pos <= mid) {
    update(x * 2, l, mid, pos, k);
  }
  if (pos > mid) {
    update(x * 2 + 1, mid + 1, r, pos, k);
  }
  pushup(x);
}
int main() {
  cin >> n >> m;
  dpow[0] = 1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    Hasha = Hasha * base + a[i];
    dpow[i] = dpow[i - 1] * base;
    sum += dpow[i - 1];
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
    pos[b[i]] = i;
  }
  for (int i = 1; i < n; i++) {
    update(1, 1, m, pos[i], i);
  }
  update(1, 1, m, pos[n], n);
  if (tr[1].val == Hasha) {
    ans++;
  }
  for (int i = n + 1; i <= m; i++) {
    update(1, 1, m, pos[i - n], 0);
    update(1, 1, m, pos[i], i);
    int d = i - n;
    if (tr[1].val == d * sum + Hasha) {
      ans++;
    }
  }
  cout << ans;
}
