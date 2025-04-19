// https://open.kattis.com/problems/howl
#include <iostream>

using namespace std;

void solve() {
    string howl;
    cin >> howl;

    int l = howl.length();

    if (howl[l - 1] == 'W')
        cout << howl + "H";
    else if (howl[l - 1] == 'H')
        cout << howl + "OO";
    else
        cout << howl + "W";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
