// https://open.kattis.com/problems/hangingout
#include <iostream>
#include <string>

using namespace std;

void solve() {
    // k - population entering or leaving
    // s - total population at present
    // c - number of times population has been denied entrance
    int L, n, k, s = 0, c = 0;
    string type;
    cin >> L >> n;
    while (n--) {
        cin >> type >> k;
        if (type == "leave") {
            s -= k;
            continue;
        }
        if ((type == "enter") && (s + k <= L)) {
            s += k;
            continue;
        }
        c++;
    }
    cout << c;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
