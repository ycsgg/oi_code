#include <cstring>
#include <deque>
#include <iostream>
using namespace std;
const int N = 3e6 + 5;
int a[N];
int n, k;
deque<int> mmin, mmax;
bool check(int x) {
    mmin.clear();
    mmax.clear();
    for (int i = 1; i < x; i++) {
        while (!mmin.empty() && a[mmin.back()] >= a[i])
            mmin.pop_back();
        while (!mmax.empty() && a[mmax.back()] <= a[i])
            mmax.pop_back();
        mmin.push_back(i);
        mmax.push_back(i);
    }
    for (int i = x; i <= n; i++) {
        while (!mmin.empty() && mmin.front() + x <= i)
            mmin.pop_front();
        while (!mmax.empty() && mmax.front() + x <= i)
            mmax.pop_front();
        while (!mmin.empty() && a[mmin.back()] >= a[i])
            mmin.pop_back();
        while (!mmax.empty() && a[mmax.back()] <= a[i])
            mmax.pop_back();
        mmin.push_back(i);
        mmax.push_back(i);
        if (a[mmax.front()] - a[mmin.front()] <= k)
            return true;
    }
    return false;
}
int main() {
    cin >> k >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int l = 0, r = n, ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            l   = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans;
    return 0;
}