// https://neetcode.io/problems/max-water-container
#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxArea(vector<int>& heights) {
        uint32_t l = 0, r = heights.size() - 1;
        uint32_t maxarea = 0;
        while (l < r) {
            int h = min(heights[l], heights[r]);
            uint32_t area = h * (r - l);
            if (maxarea < area) maxarea = area;
            if (h == heights[l])
                l++;
            else
                r--;
        }
        return maxarea;
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

        if (ans != expected)
            cout << "Testcase #" << n << ": Failed! - expected '" << expected << "' got '" << ans
                 << "'\n";
        else
            cout << "Testcase #" << n << ": Passed! Time taken: " << time_taken.count() << "ms"
                 << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto maxArea = [&](std::vector<int>& v) { return s.maxArea(v); };

    vector<TestCase> testcases = {
        {vector<int>{1, 7, 2, 5, 4, 7, 3, 6}, 36, maxArea},
        {vector<int>{2, 2, 2}, 4, maxArea},
        {vector<int>{5, 5}, 5, maxArea},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
