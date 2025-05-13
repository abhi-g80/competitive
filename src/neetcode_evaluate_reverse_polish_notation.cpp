// https://neetcode.io/problems/evaluate-reverse-polish-notation
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    int evalRPN(vector<string>& tokens) {
        stack<int> nums;
        for (string item : tokens) {
            if ((item != "+") && (item != "-") && (item != "*") && (item != "/")) {
                nums.push(stoi(item));
                continue;
            }
            int x = nums.top();
            nums.pop();
            int y = nums.top();
            nums.pop();
            if (item == "+") nums.push(y + x);
            if (item == "-") nums.push(y - x);
            if (item == "*") nums.push(y * x);
            if (item == "/") nums.push(y / x);
        }
        return nums.top();
    }
};

struct TestCase {
    vector<string> v;
    int expected;

    std::function<int(vector<string>&)> func;

    void run(int i) {
        int ans = func(v);
        if (ans != expected) {
            cout << "Testcase #" << i << ": Failed! - expected '" << expected << "' got '" << ans
                 << "'\n";
            return;
        }
        cout << "Testcase #" << i << ": Passed!\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    Solution s;

    auto evalRPN = [&](std::vector<string>& v) { return s.evalRPN(v); };

    vector<TestCase> testcases = {
        {vector<string>{"1", "2", "+", "3", "*", "4", "-"}, 5, evalRPN},
        {vector<string>{"1", "-2", "+", "3", "*", "4", "-"}, -7, evalRPN},
        {vector<string>{"1", "-2", "/"}, 0, evalRPN},
        {vector<string>{"-200", "2", "/"}, -100, evalRPN},
    };

    int i = 1;
    for (auto& testcase : testcases) {
        testcase.run(i++);
    }

    return 0;
}
