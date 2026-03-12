// https://neetcode.io/problems/palindromic-substrings/
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    int countSubstrings(string s) {
        int n = (int)s.size();
        int count = 0;
        for(int i = 0; i < n; i++) {
            int left = i, right = i;
            while((left >= 0) && (right < n) && s[left] == s[right]) {
                count++;
                left--; right++;
            }
            left = i; right = i+1;
            while((left >= 0) && (right < n) && s[left] == s[right]) {
                count++;
                left--; right++;
            }
        }
        return count;
    };
};

struct TestCase {
    string s;

    int expected;

    std::function<int(string)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        cout << "Testcase #" << n << ": ";

        auto t1 = high_resolution_clock::now();
        int ans = func(s);
        auto t2 = high_resolution_clock::now();
        duration<double, micro> time_taken = t2 - t1;
        bool failed = false;
        if (ans != expected) {
            failed = true;
            cout << "Failed! - expected '" << expected << "' got '" << ans << "'";
        }
        if (!failed) cout << "Passed!";
        cout << " Time taken: " << time_taken.count() << "ms" << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto countSubstrings = [&](string str) { return s.countSubstrings(str); };

    vector<TestCase> testcases = {
        {"abc", 3, countSubstrings},
        {"aaa", 6, countSubstrings},
        {"a", 1, countSubstrings},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
