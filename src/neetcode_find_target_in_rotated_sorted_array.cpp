// https://neetcode.io/problems/find-target-in-rotated-sorted-array
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
            if (mid < 0 || mid > nums.size()) break;
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
        int ans = func(nums, target);
        if (ans != expected) {
            cout << "Testcase #" << n << ": Failed! - expected '" << expected << "' got '" << ans
                 << "'\n";
            return;
        }
        cout << "Testcase #" << n << ": Passed!\n";
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
