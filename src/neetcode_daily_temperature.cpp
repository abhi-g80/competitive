// https://neetcode.io/problems/minimum-stack
#include <functional>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> dailyTemperatures(vector<int>& temps) {
        // stack of pair of temp and index pos
        stack<pair<int, uint32_t>> s;
        vector<int> res(temps.size());
        // 1, 3, 2, 4, 1, 1, 2
        //
        // s = [4,1,1,2] => [4,2]
        // c = [1,2,1,0,2,1,0]
        //
        for (uint32_t i = 0; i < temps.size(); i++) {
            int temp = temps[i];
            if (s.empty()) {
                s.push({temp, i});
                continue;
            }
            while (!s.empty() && s.top().first < temp) {
                res[s.top().second] = i - s.top().second;
                s.pop();
            }
            s.push({temp, i});
        }
        return res;
    }
};

struct TestCase {
    vector<int> v;
    vector<int> expected;

    std::function<vector<int>(vector<int>&)> func;

    void run(int n) {
        vector<int> ans = func(v);
        for (uint32_t i = 0; i < ans.size(); i++) {
            if (ans[i] != expected[i]) {
                cout << "Testcase #" << n << ": Failed! - expected '" << expected[i] << "' got '"
                     << ans[i] << " at index: " << i << "'\n";
                return;
            }
        }
        cout << "Testcase #" << n << ": Passed!\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto dailyTemperatures = [&](std::vector<int>& v) { return s.dailyTemperatures(v); };

    vector<TestCase> testcases = {
        // clang-format off
        {vector<int>{2, 1, 3, 1}, vector<int>{2, 1, 0, 0}, dailyTemperatures},
        {vector<int>{1,3,2,4,1,1,2}, vector<int>{1,2,1,0,2,1,0}, dailyTemperatures},
        {vector<int>{22,21,20}, vector<int>{0,0,0}, dailyTemperatures},
        {vector<int>{21,22,23,21}, vector<int>{1,1,0,0}, dailyTemperatures},
        {vector<int>{30,38,30,36,35,40,28}, vector<int>{1,4,1,2,1,0,0}, dailyTemperatures},
        // clang-format on
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
