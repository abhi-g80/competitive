// https://neetcode.io/problems/longest-repeating-substring-with-replacement/
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int characterReplacement(string s, int k) {
        // XYYX k=2
        //
        //
        unordered_map<char, int> map;
        size_t left = 0, right = 0, longest = 0;
        int maxf = 0;
        for (; right < s.size(); right++) {
            map[s[right]]++;
            maxf = max(maxf, map[s[right]]);
            while ((right - left + 1) - maxf > (size_t)k) {
                map[s[left++]]--;
            }
            longest = max(longest, right - left + 1);
        }
        return longest;
    }
};

struct TestCase {
    std::string s;
    int k;

    int expected;

    std::function<int(string, int)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        cout << "Testcase #" << n << ": ";

        auto t1 = high_resolution_clock::now();
        int ans = func(s, k);
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

    auto characterReplacement = [&](string str, int k) { return s.characterReplacement(str, k); };

    vector<TestCase> testcases = {
        {"XYYX", 2, 4, characterReplacement},
        {"ABBB", 0, 3, characterReplacement},
        {"BBAB", 0, 2, characterReplacement},
        {"BBAA", 1, 3, characterReplacement},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
