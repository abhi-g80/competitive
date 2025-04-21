// https://open.kattis.com/problems/battlesimulation
#include <cstring>
#include <iostream>
#include <unordered_map>
#define COMBO1 "RBL"
#define COMBO2 "RLB"
#define COMBO3 "LBR"
#define COMBO4 "LRB"
#define COMBO5 "BLR"
#define COMBO6 "BRL"
#define CL 3

using namespace std;

void solve() {
    string moves;
    unordered_map<char, char> counters = {
        {'R', 'S'},
        {'B', 'K'},
        {'L', 'H'},
    };

    cin >> moves;
    int ml = moves.length();

    for (int i = 0; i < ml; i++) {
        if (i + CL - 1 <= ml - 1) {
            auto s = moves.substr(i, CL);
            if (s == COMBO1 || s == COMBO2 || s == COMBO3 || s == COMBO4 || s == COMBO5 ||
                s == COMBO6) {
                cout << "C";
                i += CL - 1;
                continue;
            }
        }
        cout << counters[moves[i]];
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
