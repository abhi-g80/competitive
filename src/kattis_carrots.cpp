// https://open.kattis.com/problems/carrots
#include <iostream>
#include <string>

using namespace std;

void solve() {
    int n, p = 0;
    string stuff;
    cin >> n >> p;
    while (n--) cin >> stuff;
    cout << p;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
