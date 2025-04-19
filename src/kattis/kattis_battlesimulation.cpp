// https://open.kattis.com/problems/battlesimulation
#include <iostream>
#define CL 3

using namespace std;

void solve() {
    string moves;

    cin >> moves;
    int ml = moves.length();

    for (int i = 0; i < ml; i++) {
        if (i + CL - 1 <= ml - 1) {
            if ((moves[i] == 'R' && moves[i + 1] == 'B' && moves[i + 2] == 'L') ||
                (moves[i] == 'R' && moves[i + 1] == 'L' && moves[i + 2] == 'B') ||
                (moves[i] == 'B' && moves[i + 1] == 'L' && moves[i + 2] == 'R') ||
                (moves[i] == 'B' && moves[i + 1] == 'R' && moves[i + 2] == 'L') ||
                (moves[i] == 'L' && moves[i + 1] == 'R' && moves[i + 2] == 'B') ||
                (moves[i] == 'L' && moves[i + 1] == 'B' && moves[i + 2] == 'R')) {
                cout << "C";
                i += CL - 1;
                continue;
            }
        }
        if (moves[i] == 'R')
            cout << "S";
        else if (moves[i] == 'B')
            cout << "K";
        else
            cout << "H";
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
