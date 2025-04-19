// https://open.kattis.com/problems/acm
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void solve() {
    struct Score {
        int time;
        char problem;
        string result;
    };

    int right = 0;
    int total_score = 0;
    unordered_map<char, int> problems;
    string input;

    for (; getline(cin, input) && input != "-1";) {
        Score s;

        size_t space1 = input.find(' ');
        size_t space2 = input.find(' ', space1 + 1);

        s.time = stoi(input.substr(0, space1));
        s.problem = input[space1 + 1];
        s.result = input.substr(space2 + 1);

        if (s.result == "right") {
            right++;
            total_score += problems[s.problem] * 20 + s.time;
        } else {
            problems[s.problem]++;
        }
    }

    cout << right << " " << total_score << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
