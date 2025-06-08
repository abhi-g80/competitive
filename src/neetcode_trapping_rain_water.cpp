// https://neetcode.io/problems/trapping-rain-water
#include <chrono>
#include <climits>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int trap(vector<int>& heights) {
        // heights = 0 2 0 3 1 0 1 3 2 1
        // indices = 0 1 2 3 4 5 6 7 8 9
        //
        // solution using prefix and suffix arrays
        //
        // create 2 arrays:
        //
        //      prefix_left  = at pos i whats the max left
        //      prefix_right = at pos i whats the max right
        //
        // use the arrays to find the max water that can stored
        // at i, using
        //      min(prefix_left[i], prefix_right[i]) - heights[i]
        //
        // if this > 0 add the ans

        int s = heights.size();
        vector<int> prefix_heights(s + 1);
        vector<int> suffix_heights(s + 1);

        int curr_max = INT_MIN;
        for (int i = 0; i < s - 1; i++) {
            if (curr_max < heights[i]) curr_max = heights[i];
            prefix_heights[i + 1] = curr_max;
        }
        curr_max = INT_MIN;
        for (int i = s - 1; i >= 1; i--) {
            if (curr_max < heights[i]) curr_max = heights[i];
            suffix_heights[i - 1] = curr_max;
        }
        int ans = 0;
        for (int i = 0; i < s; i++) {
            int r = min(prefix_heights[i], suffix_heights[i]) - heights[i];
            if (r > 0) ans += r;
        }
        return ans;
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

    auto trap = [&](std::vector<int>& v) { return s.trap(v); };

    vector<TestCase> testcases = {
        {vector<int>{0, 2, 0, 3, 1, 0, 1, 3, 2, 1}, 9, trap},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
