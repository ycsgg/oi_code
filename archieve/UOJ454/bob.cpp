#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int n, m;
int p[2005];
int main() {
    fstream fin("bob.in", ios::in);
    fin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        fin >> x;
        p[x - 1] = 1;
    }
    string res;
    for (int i = 0; i < 2 * n - 2 * n % 3; i += 3) {
        cout << p[i] << p[i + 1];
        cout.flush();
        char c;
        if (p[i]) {
            cin >> c;
            res += c;
        }
        if (p[i + 1]) {
            cin >> c;
            res += c;
        }
        cin >> c;
        if (p[i + 2]) {
            res += c;
        }
    }
    char c;
    if (p[2 * n - 2 * n % 3]) {
        cin >> c;
        res += c;
    }
    if (p[2 * n - 2 * n % 3 + 1]) {
        cin >> c;
        res += c;
    }
    fstream fout("bob.out", ios::out);
    fout << res;
    return 0;
}