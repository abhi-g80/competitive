// https://open.kattis.com/problems/r2
#include <iostream>

using namespace std;

void solve() {
    int r1, s;
    cin >> r1 >> s;
    cout << 2 * s - r1;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
