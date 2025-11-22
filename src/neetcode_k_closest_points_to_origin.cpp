// https://neetcode.io/problems/k-closest-points-to-origin
#include <chrono>
#include <functional>
#include <iostream>
#include <queue>

using namespace std;

class Solution {
   public:
    struct DistGreater {
        double dist(vector<int>& x) { return x[0] * x[0] + x[1] * x[1]; }
        bool operator()(vector<int>& x, vector<int>& y) { return dist(x) > dist(y); }
    };
    vector<vector<int>> kClosest(vector<vector<int>>& nums, int k) {
        priority_queue<vector<int>, vector<vector<int>>, DistGreater> pq;
        for (auto& x : nums) pq.push(x);
        vector<vector<int>> res;
        while (res.size() < (uint32_t)k) {
            res.emplace_back(pq.top());
            pq.pop();
        }
        return res;
    }
};

struct TestCase {
    vector<vector<int>> nums;
    int k;
    vector<vector<int>> expected;

    function<vector<vector<int>>(vector<vector<int>>&, int)> func;

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
            cout << boolalpha << "Failed! - expected '";
            for (vector<int> x : expected) {
                cout << "{" << x[0] << ", " << x[1] << "}";
            }
            cout << "' got '";
            for (vector<int> x : ans) {
                cout << "{" << x[0] << ", " << x[1] << "} ";
            }
            cout << " ";
        } else {
            cout << "Passed! ";
        }
        cout << "Time taken: " << time_taken.count() << "ms" << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    Solution s;

    auto kClosest = [&](vector<vector<int>>& n, int k) { return s.kClosest(n, k); };

    vector<TestCase> testcases = {
        // order matter in the expected
        {vector<vector<int>>{{0, 2}, {2, 2}}, 1, vector<vector<int>>{{0, 2}}, kClosest},
        {vector<vector<int>>{{1, 2}, {2, 2}, {5, 5}}, 2, vector<vector<int>>{{1, 2}, {2, 2}},
         kClosest},
        {vector<vector<int>>{{0, 2}, {2, 0}, {2, 2}}, 2, vector<vector<int>>{{0, 2}, {2, 0}},
         kClosest},
        {vector<vector<int>>{{-1, 2}, {-1, -1}, {2, 2}, {1, 1}}, 2,
         vector<vector<int>>{{-1, -1}, {1, 1}}, kClosest},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }
    return 0;
}
