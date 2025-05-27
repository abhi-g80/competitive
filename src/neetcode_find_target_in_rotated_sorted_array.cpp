// https://neetcode.io/problems/find-target-in-rotated-sorted-array
#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>

using namespace std;

class Solution {
   public:
    int search(vector<int>& nums, int target) {
        int32_t r = nums.size() - 1, l = 0;
        int32_t mid;
        int index = -1;
        while (l <= r) {
            mid = (r - l) / 2 + l;
            if (nums[mid] == target) {
                index = mid;
                break;
            }
            if (nums[l] <= nums[mid]) {
                // left sorted
                if (target < nums[mid] && target >= nums[l])
                    r = mid - 1;
                else
                    l = mid + 1;
            } else {
                // right sorted
                if (target > nums[mid] && target <= nums[r])
                    l = mid + 1;
                else
                    r = mid - 1;
            }
        }
        return index;
    }
};

struct TestCase {
    vector<int> nums;
    int target;
    int expected;

    function<int(vector<int>&, int)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        auto t1 = high_resolution_clock::now();
        int ans = func(nums, target);
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
    Solution s;

    auto search = [&](vector<int>& n, int t) { return s.search(n, t); };

    vector<TestCase> testcases = {
        {vector<int>{1, 4}, 1, 0, search},
        {vector<int>{1, 4}, 4, 1, search},
        {vector<int>{4, 1}, 4, 0, search},
        {vector<int>{4, 1}, 1, 1, search},
        {vector<int>{3, 5, -1, 0}, 6, -1, search},
        {vector<int>{3, 5, -1, 0}, -1, 2, search},
        {vector<int>{7, 1, 2, 3, 4, 5, 6}, 5, 5, search},
        {vector<int>{-1}, 6, -1, search},
        {vector<int>{-1}, -1, 0, search},
        {vector<int>{1}, 0, -1, search},
        {vector<int>{-1, 2}, 0, -1, search},
        {vector<int>{1, -2}, -2, 1, search},
        {vector<int>{1, 3}, 0, -1, search},
        {vector<int>{1, 3}, 4, -1, search},
        {vector<int>{3, 4, 5, 6, 0}, 0, 4, search},
        {vector<int>{3, 4, 5, 6, 1, 2}, 1, 4, search},
        {vector<int>{3, 4, 5, 6, 1, 2}, 2, 5, search},
        {vector<int>{3, 5, 6, 0, 1, 2}, 4, -1, search},
        {vector<int>{3, 4, 6, 0, 1, 2}, 4, 1, search},
        {vector<int>{3, 5, 6, -1, 1, 2}, 0, -1, search},
        {vector<int>{3, 5, 6, -1, 1, 2}, 2, 5, search},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }
    return 0;
}
