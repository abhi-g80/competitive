// https://leetcode.com/problems/min-cost-to-connect-all-points/
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        auto cost = [&](vector<int>& a, vector<int>& b) {
            return abs(a[0] - b[0]) + abs(a[1] - b[1]);
        };
        priority_queue<pair<int, int>> pq;
        vector<bool> visited(points.size(), false);
        auto p = 0;
        int total_cost = 0;
        size_t connect = 0;
        while (++connect < points.size()) {
            visited[p] = true;
            for (size_t i = 0; i < points.size(); i++) {
                if (visited[i]) continue;
                pq.push(pair<int, int>{-cost(points[i], points[p]), (int)i});
            }
            while (visited[pq.top().second]) pq.pop();
            total_cost -= pq.top().first;
            p = pq.top().second;
            pq.pop();
        }
        return total_cost;
    }
};

struct TestCase {
    vector<vector<int>> points;
    int expected;

    std::function<int(vector<vector<int>>&)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        cout << "Testcase #" << n << ": ";

        auto t1 = high_resolution_clock::now();
        int ans = func(points);
        auto t2 = high_resolution_clock::now();
        duration<double, micro> time_taken = t2 - t1;
        bool failed = false;
        if (ans != expected) {
            failed = true;
            cout << "Failed! - expected '" << expected << "' got '" << ans << "'";
        }
        if (!failed) cout << "Passed!";
        cout << "\nTime taken: " << time_taken.count() << "ms" << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto minCostConnectPoints = [&](std::vector<vector<int>>& points) {
        return s.minCostConnectPoints(points);
    };

    vector<TestCase> testcases = {
        {vector<vector<int>>{{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}}, 20, minCostConnectPoints},
        {vector<vector<int>>{{3, 12}, {-2, 5}, {-4, 1}}, 18, minCostConnectPoints},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
