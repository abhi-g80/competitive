// https://neetcode.io/problems/median-of-two-sorted-arrays
#include <chrono>
#include <climits>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // nums1 = [3, 5, 7]     length - 3
        // nums2 = [1, 4, 8, 9]  length - 4
        //
        // merge sorted = [1, 3, 4, 5, 7, 8, 9] -> median 5
        //
        // partitionNums1 + partitionNums2 = (x + y + 1)/2
        //
        // partitionNum1
        //           start = 0
        //           end   = 2
        //           mid   = 0 + (2-0)/2 = 1
        //
        // partitonNums2
        //           = (3+4)/2 - 1
        //           = 3 - 1 = 2
        //
        //  nums1[1] = 5
        //  nums2[2] = 8
        //
        //  max_nums1_left, min_nums1_right
        //  max_nums2_left, min_nums2_right
        //
        //  max_nums2_left <= min_nums1_right
        //  max_nums1_left <= min_nums2_right
        //
        int s1 = nums1.size();
        int s2 = nums2.size();

        vector<int>* min_a = &nums1;
        vector<int>* max_a = &nums2;
        if (s2 < s1) {
            min_a = &nums2;
            max_a = &nums1;
        }

        float median = 0.0;

        int32_t l = 0, r = min_a->size();
        int32_t x = min_a->size(), y = max_a->size();

        while (l <= r) {
            int mid = l + (r - l) / 2;
            int p = (x + y + 1) / 2 - mid;

            int min_a_left = mid > 0 ? (*min_a)[mid - 1] : INT_MIN;
            int min_a_right = mid < x ? (*min_a)[mid] : INT_MAX;
            int max_a_left = p > 0 ? (*max_a)[p - 1] : INT_MIN;
            int max_a_right = p < y ? (*max_a)[p] : INT_MAX;

            if (min_a_left <= max_a_right && max_a_left <= min_a_right) {
                if ((x + y) & 1) {
                    median = (static_cast<float>(max(min_a_left, max_a_left)));
                } else {
                    int m = max(min_a_left, max_a_left);
                    int n = min(min_a_right, max_a_right);
                    median = static_cast<float>(m + n) / 2;
                }
                break;
            }
            if (min_a_left > max_a_right)
                r = mid - 1;
            else
                l = mid + 1;
        }

        return median;
    }
};

struct TestCase {
    vector<int> nums1;
    vector<int> nums2;
    double expected;

    function<double(vector<int>&, vector<int>&)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        auto t1 = high_resolution_clock::now();
        double ans = func(nums1, nums2);
        auto t2 = high_resolution_clock::now();
        duration<double, micro> time_taken = t2 - t1;

        cout << boolalpha << "Testcase #" << n << ": ";

        if (ans != expected) {
            cout << "Failed! - expected '" << expected << "'\tgot '" << ans << "'";
        } else
            cout << "Passed!";
        cout << "\tTime taken: " << time_taken.count() << "ms"
             << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    Solution s;

    auto findMedianSortedArrays = [&](vector<int>& n, vector<int>& m) {
        return s.findMedianSortedArrays(n, m);
    };

    vector<TestCase> testcases = {
        // clang-format off
        {vector<int>{3, 5, 7}, vector<int>{1, 4, 8, 9}, 5.0, findMedianSortedArrays},
        {vector<int>{3, 5, 7, 8}, vector<int>{1, 4, 8, 9}, 6, findMedianSortedArrays}, // 1, 3, 4, 5, 7, 8, 8, 9
        {vector<int>{1, 2, 3, 4, 5}, vector<int>{1, 3, 4, 5}, 3.0, findMedianSortedArrays}, // 1 1 2 3 3 4 4 5 5
        {vector<int>{1, 4}, vector<int>{3}, 3.0, findMedianSortedArrays},
        {vector<int>{1, 3}, vector<int>{2, 4}, 2.5, findMedianSortedArrays},
        {vector<int>{1, 3, 5}, vector<int>{2, 4}, 3.0, findMedianSortedArrays}, // 1 2 3 4 5
        {vector<int>{1, 3, 5}, vector<int>{2, 4, 6}, 3.5, findMedianSortedArrays}, // 1 2 3 4 5 6
        {vector<int>{1, 3, 5}, vector<int>{2, 4, 6, 7}, 4, findMedianSortedArrays}, // 1 2 3 4 5 6 7
        {vector<int>{3, 5}, vector<int>{2, 4, 6, 7}, 4.5, findMedianSortedArrays}, // 2 3 4 5 6 7
        // clang-format on
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }
    return 0;
}
