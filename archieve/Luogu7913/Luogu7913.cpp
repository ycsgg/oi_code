#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
const int N = 2e5 + 10;
int n, m1, m2;
struct Data {
    int x, typ, id;
} a[N], b[N];

int tima[N], timb[N];

void prepare(Data *a, int len, int *res) {
    multiset<int> mex;
    for (int i = 1; i <= len; i++) {
        mex.insert(i);
    }
    for (int i = 1; i <= len; i++) {
        if (a[i].typ == -1) {
            mex.insert(res[a[i].id]);
        } else {
            res[a[i].id] = *mex.begin();
            mex.erase(mex.find(res[a[i].id]));
        }
    }
}
int dfa[N], dfb[N];
int main() {
    cin >> n >> m1 >> m2;
    for (int i = 1; i <= m1; i++) {
        cin >> a[2 * i - 1].x >> a[2 * i].x;
        a[2 * i - 1].typ = 1;
        a[2 * i].typ = -1;
        a[2 * i - 1].id = a[2 * i].id = i;
    }
    for (int i = 1; i <= m2; i++) {
        cin >> b[2 * i - 1].x >> b[2 * i].x;
        b[2 * i - 1].typ = 1;
        b[2 * i].typ = -1;
        b[2 * i - 1].id = b[2 * i].id = i;
    }
    sort(a + 1, a + 1 + 2 * m1, [&](const auto &A, const auto &B) -> bool {
        return A.x < B.x;
    });
    sort(b + 1, b + 1 + 2 * m2, [&](const auto &A, const auto &B) -> bool {
        return A.x < B.x;
    });

    prepare(a, m1 * 2, tima);
    prepare(b, m2 * 2, timb);

    for (int i = 1; i <= m1; i++) {
        dfa[tima[i]]++;
    }
    for (int i = 1; i <= m2; i++) {
        dfb[timb[i]]++;
    }

    int sumb = 0, suma = 0;

    for (int i = 1; i <= n; i++) {
        sumb += dfb[i];
    }

    int mmax = sumb;

    for (int i = 1; i <= n; i++) {
        suma += dfa[i];
        sumb -= dfb[n - i + 1];
        mmax = max(mmax, suma + sumb);
    }

    cout << mmax;
}