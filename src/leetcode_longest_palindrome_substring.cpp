// https://leetcode.com/problems/longest-palindromic-substring/
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    string longestPalindrome(string s) {
        int max_length = 0, idx = 0;
        int n = (int)s.size();
        for (int i = 0; i < n; i++) {
            int left = i, right = i;
            while ((left >= 0) && (right < n) && (s[left] == s[right])) {
                if ((right - left + 1) > max_length) {
                    idx = left;
                    max_length = right - left + 1;
                }
                left--;
                right++;
            }
            left = i;
            right = i + 1;
            while ((left >= 0) && (right < n) && (s[left] == s[right])) {
                if ((right - left + 1) > max_length) {
                    idx = left;
                    max_length = right - left + 1;
                }
                left--;
                right++;
            }
        }
        return s.substr(idx, max_length);
    };
};

struct TestCase {
    string s;

    string expected;

    std::function<string(string)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        cout << "Testcase #" << n << ": ";

        auto t1 = high_resolution_clock::now();
        string ans = func(s);
        auto t2 = high_resolution_clock::now();
        duration<double, micro> time_taken = t2 - t1;
        bool failed = false;
        if (ans != expected) {
            failed = true;
            cout << "Failed! - expected '" << expected << "' got '" << ans << "'";
        }
        if (!failed) cout << "Passed!";
        cout << "\nTime taken: " << time_taken.count() << "ms" << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto longestPalindrome = [&](string str) { return s.longestPalindrome(str); };

    vector<TestCase> testcases = {
        {"aab", "aa", longestPalindrome},
        {"xxx", "xxx", longestPalindrome},
        {"yy", "yy", longestPalindrome},
        {"aacaabbassease", "aacaa", longestPalindrome},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
