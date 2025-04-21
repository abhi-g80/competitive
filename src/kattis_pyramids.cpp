// https://open.kattis.com/problems/pyramids
#include <iostream>

using namespace std;

void solve() {
    uint64_t n, s = 0, l = 0;
    for (cin >> n; (s += 4 * l * l + 4 * l + 1) <= n; l += 1) {
    }
    cout << l;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
//
