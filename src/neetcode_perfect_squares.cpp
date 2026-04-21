// https://neetcode.io/problems/perfect-squares/
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numSquares(int n) {
        vector<int> dp(n + 1, n + 1);
        vector<int> ps;

        for (int i = 1; i < int(sqrt(n)) + 2; i++) ps.push_back(i * i);

        dp[0] = 0;
        for (int i = 1; i < n + 1; i++) {
            for (int sq : ps) {
                if (i - sq >= 0) dp[i] = min(dp[i], dp[i - sq] + 1);
            }
        }
        return dp[n];
    };
};

struct TestCase {
    int input;

    int expected;

    std::function<int(int)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        cout << "Testcase #" << n << ": ";

        auto t1 = high_resolution_clock::now();
        int ans = func(input);
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

    auto numSquares = [&](int n) { return s.numSquares(n); };

    vector<TestCase> testcases = {
        {13, 2, numSquares},   {6, 3, numSquares},    {26, 2, numSquares},
        {9999, 4, numSquares}, {4096, 1, numSquares}, {10000, 1, numSquares},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
