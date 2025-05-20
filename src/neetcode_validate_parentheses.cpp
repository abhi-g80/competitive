// https://neetcode.io/problems/validate-parentheses
#include <cstdint>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isValid2(string s) {
        stack<char> v;
        unordered_map<char, char> m{
            make_pair('}', '{'),
            make_pair(']', '['),
            make_pair(')', '('),
        };

        for (const char& e : s) {
            if (v.empty()) {
                v.push(e);
                continue;
            }
            if (v.top() == m[e])
                v.pop();
            else
                v.push(e);
        }

        return v.empty();
    }
    bool isValid(string s) {
        vector<char> stack(s.size() + 1);

        uint32_t i = 0;
        for (const char& e : s) {
            if (e == '}' && i > 0 && stack[i - 1] != '{')
                return false;
            else if (e == '}' && i > 0 && stack[i - 1] == '{') {
                stack[i - 1] = 0;
                i--;
                continue;
            }

            if (e == ')' && i > 0 && stack[i - 1] != '(')
                return false;
            else if (e == ')' && i > 0 && stack[i - 1] == '(') {
                stack[i - 1] = 0;
                i--;
                continue;
            }

            if (e == ']' && i > 0 && stack[i - 1] != '[')
                return false;
            else if (e == ']' && i > 0 && stack[i - 1] == '[') {
                stack[i - 1] = 0;
                i--;
                continue;
            }
            stack[i++] = e;
        }
        return i == 0 ? true : false;
    }
};

struct TestCase {
    string v;
    bool expected;

    std::function<bool(string)> func;

    void run(int i) {
        bool ans = func(v);
        if (ans != expected) {
            cout << boolalpha << "Testcase #" << i << ": Failed! - expected '" << expected
                 << "' got '" << ans << "'\n";
            return;
        }
        cout << "Testcase #" << i << ": Passed!\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    Solution s;

    auto isValid = [&](string v) { return s.isValid(v); };
    auto isValid2 = [&](string v) { return s.isValid2(v); };

    vector<TestCase> testcases = {
        {"[]", true, isValid},     {"[]", true, isValid2},    {"[(])", false, isValid},
        {"[(])", false, isValid2}, {"([{}])", true, isValid}, {"([{}])", true, isValid2},
        {"({[)", false, isValid},  {"({[)", false, isValid2},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
