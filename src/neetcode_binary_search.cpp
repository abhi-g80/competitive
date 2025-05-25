// https://neetcode.io/problems/binary-search
#include <cstdint>
#include <functional>
#include <iostream>

using namespace std;

class Solution {
   public:
    int search(vector<int>& nums, int target) {
        int32_t r = nums.size(), l = 0;
        int32_t mid = (r - l) / 2 + l;
        int index = -1;
        while (l <= r) {
            if (nums[mid] == target) {
                index = mid;
                break;
            }
            if (nums[mid] > target)
                r = mid - 1;
            else
                l = mid + 1;
            mid = (r - l) / 2 + l;
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
        {vector<int>{-1, 0, 3, 5}, 6, -1, search},
        {vector<int>{-1}, 6, -1, search},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }
    return 0;
}
