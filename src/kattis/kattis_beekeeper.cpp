// https://open.kattis.com/problems/beekeeper
#include <iostream>

using namespace std;

void solve() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        int max_counter = 0;
        string best, word;
        while (n--) {
            cin >> word;
            int l = word.length();
            int counter = 0;
            for (int i = 0; i < l - 1; i++) {
                if (((word[i] == 'a') && (word[i + 1] == 'a')) ||
                    ((word[i] == 'e') && (word[i + 1] == 'e')) ||
                    ((word[i] == 'i') && (word[i + 1] == 'i')) ||
                    ((word[i] == 'o') && (word[i + 1] == 'o')) ||
                    ((word[i] == 'u') && (word[i + 1] == 'u')) ||
                    ((word[i] == 'y') && (word[i + 1] == 'y')))
                    counter++;
            }
            // cout << "max_counter: " << max_counter <<  " word: " << word << " counter: " <<
            // counter << "\n";
            if (counter >= max_counter) {
                best = word;
                max_counter = counter;
            }
        }
        cout << best << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
