// https://open.kattis.com/problems/pokerhand
#include <iostream>
#include <map>
#include <string>

using namespace std;

void solve() {
    map<char, int> m;
    int l = 1;
    string k;
    for (int i = 0; i < 5; i++) {
        cin >> k;
        if (auto s = m.find(k[0]); s == m.end()) {
            m[k[0]] = 1;
            continue;
        }
        m[k[0]] += 1;
        if (m[k[0]] > l) l = m[k[0]];
    }
    cout << l;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
