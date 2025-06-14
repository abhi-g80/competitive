// https://neetcode.io/problems/buy-and-sell-crypto
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        int curr_min = INT_MAX;
        for (uint32_t i = 0; i < prices.size(); i++) {
            if (prices[i] < curr_min) curr_min = prices[i];
            int32_t v = prices[i] - curr_min;
            if (v > 0 && v > profit) profit = v;
        }
        return profit;
    }
};

struct TestCase {
    vector<int> v;
    int expected;

    std::function<int(vector<int>&)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        auto t1 = high_resolution_clock::now();
        int ans = func(v);
        auto t2 = high_resolution_clock::now();
        duration<double, micro> time_taken = t2 - t1;

        cout << boolalpha << "Testcase #" << n << ": ";

        if (ans != expected) {
            cout << "Failed! - expected '" << expected << "' got '" << ans << "'";
        } else
            cout << "Passed!";
        cout << " Time taken: " << time_taken.count() << "ms"
             << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto maxProfit = [&](std::vector<int>& v) { return s.maxProfit(v); };

    vector<TestCase> testcases = {
        {vector<int>{10, 1, 5, 6, 7, 1}, 6, maxProfit},
        {vector<int>{10, 8, 7, 5, 2}, 0, maxProfit},
        {vector<int>{5, 1, 2, 1, 3}, 2, maxProfit},
        {vector<int>{2, 4, 1}, 2, maxProfit},
        {vector<int>{5, 20, 1, 2, 3, 4, 5}, 15, maxProfit},
        {vector<int>{100}, 0, maxProfit},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
