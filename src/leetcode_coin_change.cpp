// https://leetcode.com/problems/coin-change/
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int coinChange(vector<int>& coins, int amount) {
        if(amount == 0) return 0;
        vector<int> dp(amount+1);
        dp[0] = 0;
        for(int i = 1; i < amount+1; i++) dp[i] = amount+1; // max out the num of ways
        for(const int& coin: coins) if(coin <= amount) dp[coin] = 1; // make the coins 1
        for(int i = 1; i < amount+1; i++) {
            for(const int& coin: coins) {
                if(i >= coin) dp[i] = min(1+dp[i-coin], dp[i]);
            }
        }
        // cout << "\nways: " << dp[amount] << "\n";
        return (dp[amount]>amount)? -1: dp[amount];
    };
};

struct TestCase {
    vector<int> coins;
    int amount;

    int expected;

    std::function<int(vector<int>, int)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        cout << "Testcase #" << n << ": ";

        auto t1 = high_resolution_clock::now();
        int ans = func(coins, amount);
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

    auto coinChange = [&](vector<int> coins, int amount) { return s.coinChange(coins, amount); };

    vector<TestCase> testcases = {
        {vector<int>{1,2,5}, 11, 3, coinChange},
        {vector<int>{2}, 3, -1, coinChange},
        {vector<int>{1}, 0, 0, coinChange},
        {vector<int>{1,2,5}, 100, 20, coinChange},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
