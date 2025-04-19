// https://open.kattis.com/problems/bossbattle
#include <iostream>

using namespace std;

void solve() {
    int n;
    cin >> n;
    n > 3 ? cout << n - 2 : cout << 1;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
