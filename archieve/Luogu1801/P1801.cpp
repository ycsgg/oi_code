
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N = 2e6 + 5;
typedef priority_queue<int> qmax;
typedef priority_queue<int, vector<int>, greater<int>> qmin;
qmax mmax;
qmin mmin;
int n, m;
int a[N];
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  int now = 1;
  for (int i = 1; i <= m; i++) {
    int x;
    cin >> x;
    for (int j = now; j <= x; j++) {
      mmax.push(a[j]);
      if (mmax.size() == i) {
        mmin.push(mmax.top());
        mmax.pop();
      }
    }
    now = x + 1;
    cout << mmin.top() << endl;
    mmax.push(mmin.top());
    mmin.pop();
  }
  return 0;
}
