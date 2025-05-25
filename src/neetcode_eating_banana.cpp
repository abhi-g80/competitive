// https://neetcode.io/problems/eating-bananas
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
    int minEatingSpeed(vector<int>& piles, int h) {
        int32_t maxval = INT_MIN;
        for (int p : piles)
            if (p > maxval) maxval = p;
        int32_t l = 1, r = maxval;
        int32_t mid = (r - l) / 2 + l;
        while (l <= r) {
            uint64_t hcalc = 0;
            for (uint32_t i = 0; i < piles.size(); i++) {
                hcalc += ceil(static_cast<double>(piles[i]) / mid);
            }
            if (hcalc <= h) r = mid - 1;
            if (hcalc > h) l = mid + 1;
            mid = (r - l) / 2 + l;
        }
        return mid;
    }
};

struct TestCase {
    vector<int> v;
    int target;
    int expected;

    std::function<int(vector<int>&, int)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        auto t1 = high_resolution_clock::now();
        int ans = func(v, target);
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

    auto minEatingSpeed = [&](std::vector<int>& v, int t) { return s.minEatingSpeed(v, t); };

    vector<TestCase> testcases = {
        {vector<int>{1, 4, 3, 2}, 9, 2, minEatingSpeed},
        {vector<int>{25, 10, 23, 4}, 4, 25, minEatingSpeed},
        {vector<int>{25}, 1, 25, minEatingSpeed},
        {vector<int>{3, 3}, 7, 1, minEatingSpeed},
        {vector<int>{3, 6, 7, 11}, 8, 4, minEatingSpeed},
        {vector<int>{31232323}, 31232322, 2, minEatingSpeed},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
