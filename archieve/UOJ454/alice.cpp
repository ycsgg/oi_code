#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int n, m;
string s;
int main() {
    fstream fin("alice.in", ios::in);
    fin >> n >> m >> s;
    for (int i = 0; i < 2 * n - 2 * n % 3; i += 3) {
        char c;
        cin >> c;
        if (c == '1') {
            cout << s[i];
        }
        cin >> c;
        if (c == '1') {
            cout << s[i + 1];
        }
        cout << s[i + 2];
        cout.flush();
    }
    cout << s[2 * n - 2 * n % 3] << s[2 * n - 2 * n % 3 + 1];
    cout.flush();
}