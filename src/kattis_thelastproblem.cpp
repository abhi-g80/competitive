// https://open.kattis.com/problems/thelastproblem
#include <iostream>
#include <string>

using namespace std;

void solve() {
    string s;
    getline(cin, s);
    cout << "Thank you, " << s << ", and farewell!";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
