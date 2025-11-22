// https://neetcode.io/problems/kth-largest-element-in-an-array
#include <chrono>
#include <functional>
#include <iostream>
#include <queue>

using namespace std;

class Solution {
   public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, less<int>> pq;
        for (auto& x : nums) pq.push(x);
        for (int i = 0; i < k - 1; i++) pq.pop();
        return pq.top();
    }
};

struct TestCase {
    vector<int> nums;
    int k;
    int expected;

    function<int(vector<int>&, int)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        cout << "Testcase #: " << n << " ";

        auto t1 = high_resolution_clock::now();
        auto ans = func(nums, k);
        auto t2 = high_resolution_clock::now();
        duration<double, micro> time_taken = t2 - t1;
        if (ans != expected) {
            cout << boolalpha << "Failed! - expected '" << expected << "' got '" << ans << "'";
        } else {
            cout << "Passed! ";
        }
        cout << "Time taken: " << time_taken.count() << "ms" << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    Solution s;

    auto findKthLargest = [&](vector<int>& n, int k) { return s.findKthLargest(n, k); };

    vector<TestCase> testcases = {
        {vector<int>{0, 2, 2, 2}, 1, 2, findKthLargest},
        {vector<int>{0, 2, 2, 2}, 2, 2, findKthLargest},
        {vector<int>{0, 2, 2, 2}, 3, 2, findKthLargest},
        {vector<int>{6, 3, 5, 1}, 3, 3, findKthLargest},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }
    return 0;
}
