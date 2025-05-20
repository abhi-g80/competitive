// https://neetcode.io/problems/two-integer-sum-ii
#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> twoSums(vector<int>& numbers, int target) {
        int32_t i = 0, j = numbers.size() - 1;
        while (i < j) {
            if (numbers[i] + numbers[j] > target)
                j--;
            else if (numbers[i] + numbers[j] < target)
                i++;
            else
                break;
        }
        return vector<int>{i + 1, j + 1};
    }
};

struct TestCase {
    vector<int> v;
    int target;
    vector<int> expected;

    std::function<vector<int>(vector<int>&, int)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        auto t1 = high_resolution_clock::now();
        vector<int> ans = func(v, target);
        auto t2 = high_resolution_clock::now();
        duration<double, micro> time_taken = t2 - t1;

        for (uint32_t i = 0; i < ans.size(); i++) {
            if (ans[i] != expected[i]) {
                cout << "Testcase #" << n << ": Failed! - expected '" << expected[i] << "' got '"
                     << ans[i] << " at index: " << i << "'\n";
                return;
            }
        }
        cout << "Testcase #" << n << ": Passed! Time taken: " << time_taken.count() << "ms"
             << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto twoSums = [&](std::vector<int>& v, int t) { return s.twoSums(v, t); };

    vector<TestCase> testcases = {
        {vector<int>{1, 2, 3, 4}, 3, vector<int>{1, 2}, twoSums},
        {vector<int>{-1, -1, 0, 2}, -2, vector<int>{1, 2}, twoSums},
        {vector<int>{-1, -1, 0, 2}, 2, vector<int>{3, 4}, twoSums},
        {vector<int>{-1000, 1000}, 0, vector<int>{1, 2}, twoSums},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
