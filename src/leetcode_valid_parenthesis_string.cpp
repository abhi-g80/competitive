// https://leetcode.com/problems/valid-parenthesis-string/
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    bool checkValidString(string s) {
        // (*) - stack based approach
        // left and star;
        //
        stack<int> left, star;
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] == '(')
                left.push(i);
            else if (s[i] == '*')
                star.push(i);
            else {
                if (!left.empty())
                    left.pop();
                else if (!star.empty())
                    star.pop();
                else
                    return false;
            }
        }
        while (!left.empty()) {
            if (star.empty() || (star.top() < left.top())) return false;
            left.pop();
            star.pop();
        }
        return true;
    }
};

struct TestCase {
    std::string s;

    int expected;

    std::function<bool(string)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        cout << "Testcase #" << n << ": ";

        auto t1 = high_resolution_clock::now();
        bool ans = func(s);
        auto t2 = high_resolution_clock::now();
        duration<double, micro> time_taken = t2 - t1;
        bool failed = false;
        if (ans != expected) {
            failed = true;
            cout << boolalpha << "Failed! - expected '" << expected << "' got '" << ans << "'";
        }
        if (!failed) cout << "Passed!";
        cout << "\nTime taken: " << time_taken.count() << "ms" << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto checkValidString = [&](string str) { return s.checkValidString(str); };

    vector<TestCase> testcases = {
        {"()", true, checkValidString},
        {"(*()))", true, checkValidString},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
