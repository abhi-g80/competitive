// https://neetcode.io/problems/search-2d-matrix
#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>

using namespace std;

class Solution {
   public:
    bool search(vector<vector<int>>& matrix, int target) {
        // search on the last column to detect the rows
        int32_t row_u = 0, row_d = matrix.size() - 1;
        int32_t col_r = matrix[0].size() - 1;
        int32_t row_f = -1;
        int32_t row_mid = (row_d - row_u) / 2 + row_u;
        row_f = row_mid;
        while (row_u < row_d) {
            /* cout << "row_u = " << row_u << " row_d = " << row_d << " row_mid = " << row_mid <<
             * "\n"; */
            if (matrix[row_mid][col_r] == target) {
                return true;
            }
            if (row_d - row_u == 1) {
                if (matrix[row_u][col_r] < target && matrix[row_d][col_r] >= target) {
                    row_f = row_d;
                    break;
                } else if (matrix[row_u][col_r] <= target && matrix[row_d][col_r] > target) {
                    row_f = row_u;
                    break;
                } else if (matrix[row_d][col_r] < target)
                    return false;
            }
            if (matrix[row_mid][col_r] > target) {
                row_d = row_mid;
            } else {
                row_u = row_mid;
            }
            row_mid = (row_d - row_u) / 2 + row_u;
            row_f = row_mid;
        }
        /* cout << "row_f = " << row_f << "\n"; */

        int32_t l = 0, r = matrix[0].size();
        int32_t mid = (r - l) / 2 + l;
        while (l <= r) {
            if (mid < 0 || mid >= matrix[0].size()) return false;
            if (matrix[row_f][mid] == target) return true;
            if (matrix[row_f][mid] > target)
                r = mid - 1;
            else
                l = mid + 1;
            mid = (r - l) / 2 + l;
        }
        return false;
    }
    // Use the fact that the matrix is actually a sorted
    // vector.
    bool search2(vector<vector<int>>& matrix, int target) {
        int32_t rows = matrix.size(), cols = matrix[0].size();
        int32_t l = 0, r = rows * cols - 1;
        int32_t mid = (r - l) / 2 + l;
        int32_t mid_r = mid / cols, mid_c = mid % cols;
        while (l <= r) {
            if (matrix[mid_r][mid_c] == target) return true;
            if (matrix[mid_r][mid_c] > target)
                r = mid - 1;
            else
                l = mid + 1;
            mid = (r - l) / 2 + l;
            mid_r = mid / cols;
            mid_c = mid % cols;
        }
        return false;
    }
};

struct TestCase {
    vector<vector<int>> matrix;
    int target;
    bool expected;

    function<bool(vector<vector<int>>&, int)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        auto t1 = high_resolution_clock::now();
        bool ans = func(matrix, target);
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

    auto search = [&](vector<vector<int>>& n, int t) { return s.search2(n, t); };

    vector<TestCase> testcases = {
        {vector<vector<int>>{{1, 2, 4, 8}, {10, 11, 12, 13}, {14, 20, 30, 40}}, 2, true, search},
        {vector<vector<int>>{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 3, true, search},
        {vector<vector<int>>{{1, 2, 4, 8}, {10, 11, 12, 13}, {14, 20, 30, 40}}, 12, true, search},
        {vector<vector<int>>{{1, 2, 4, 8}, {10, 11, 12, 13}, {14, 20, 30, 40}}, 30, true, search},
        {vector<vector<int>>{{1, 2, 4, 8}, {10, 11, 12, 13}, {14, 20, 30, 40}}, 1, true, search},
        {vector<vector<int>>{{1, 2, 4, 8}, {10, 11, 12, 13}, {14, 20, 30, 40}}, 10, true, search},
        {vector<vector<int>>{{1, 2, 4, 8}, {10, 11, 12, 13}, {14, 20, 30, 40}}, 14, true, search},
        {vector<vector<int>>{{1, 2, 4, 8}, {10, 11, 12, 13}, {14, 20, 30, 40}}, 15, false, search},
        {vector<vector<int>>{{1}, {10}, {14}}, 15, false, search},
        {vector<vector<int>>{{2}, {10}, {14}}, 1, false, search},
        {vector<vector<int>>{{2}, {10}, {14}}, 2, true, search},
        {vector<vector<int>>{{2}, {10}, {14}}, 14, true, search},
        {vector<vector<int>>{{1}}, 14, false, search},
        {vector<vector<int>>{{1}}, 1, true, search},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }
    return 0;
}
