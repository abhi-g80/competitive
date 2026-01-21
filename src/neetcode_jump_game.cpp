// https://neetcode.io/problems/jump-game
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canJump(vector<int>& jumps) {
        // jumps = [2, 3, 1, 1, 4]
        //
        // try to scan from curr pos to max and see how much further can
        // we go.
        //
        // jumps = [3,2,1,0,4]
        //
        // false
        //
        //
        // jumps = [3,0,8,2,0,0,1]
        //
        // true
        //
        // jumps = 1,2,0,1,5,0,2,0,0,1,0
        // jumps = 1,1,2,2,0,1,1
        //
        // true

        int n = jumps.size();
        if (n <= 1) return true;
        int curr_pos = 0;
        while (true) {
            int max_reach = -1;
            int pos = -1;
            for (int i = curr_pos + 1; i <= min(curr_pos + jumps[curr_pos], n - 1); i++) {
                if (i + jumps[i] >= max_reach) {
                    max_reach = jumps[i] + i;
                    pos = i;
                }
                if (pos >= n - 1 || pos + jumps[pos] >= n - 1) return true;
            }
            if (curr_pos == pos) return false;
            curr_pos = pos;
        }
        assert(false);
    }
};

struct TestCase {
    vector<int> v;
    bool expected;

    std::function<bool(vector<int>&)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        cout << "Testcase #" << n << ": ";

        auto t1 = high_resolution_clock::now();
        bool ans = func(v);
        auto t2 = high_resolution_clock::now();
        duration<double, micro> time_taken = t2 - t1;
        if (ans != expected) {
            cout << boolalpha << "Failed! - expected '" << expected << "' got '" << ans << "'";
        } else {
            cout << "Passed! ";
        }
        cout << "\nTime taken: " << time_taken.count() << "ms" << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto canJump = [&](std::vector<int>& v) { return s.canJump(v); };

    vector<TestCase> testcases = {
        {vector<int>{2, 3, 1, 1, 4}, true, canJump},
        {vector<int>{3, 2, 1, 0, 4}, false, canJump},
        {vector<int>{1}, true, canJump},
        {vector<int>{3, 0, 8, 2, 0, 0, 1}, true, canJump},
        {vector<int>{1, 2, 0, 1, 5, 0, 2, 0, 0, 1, 0}, true, canJump},
        {vector<int>{1, 1, 2, 2, 0, 1, 1}, true, canJump},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
