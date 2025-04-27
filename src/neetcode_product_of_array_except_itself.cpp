// https://neetcode.io/problems/products-of-array-discluding-self
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> productExceptSelf2(vector<int>& nums) {
        vector<int> prefix_p(nums.size() + 1);
        vector<int> suffix_p(nums.size() + 1);

        int p = 1;
        for (uint32_t i = 0; i < nums.size(); i++) {
            prefix_p[i] = p;
            p *= nums[i];
        }
        p = 1;
        for (uint32_t i = nums.size() - 1; (i >= 0) && (i < nums.size()); i--) {
            suffix_p[i] = p;
            p *= nums[i];
        }
        vector<int> res(nums.size() + 1);
        for (uint32_t i = 0; i < nums.size(); i++) {
            res[i] = prefix_p[i] * suffix_p[i];
        }
        return res;
    }

    vector<int> productExceptSelf(vector<int>& nums) {
        int prod = 1;
        bool all_zeros = true;
        int num_zeros = 0;
        for (auto i : nums) {
            if (i != 0) {
                prod *= i;
                all_zeros = false;
            } else {
                num_zeros += 1;
            }
        }
        if (all_zeros) prod = 0;
        vector<int> res;
        for (uint32_t i = 0; i < nums.size(); i++) {
            if (num_zeros > 1) {
                res.push_back(0);
                continue;
            }
            if (nums[i] == 0) {
                res.push_back(prod);
                continue;
            }
            if (num_zeros == 1) {
                res.push_back(0);
                continue;
            }
            res.push_back(prod / nums[i]);
        }
        return res;
    }
};

Solution s;

void runTests(int tnum, vector<int>& nums, vector<int>& expected) {
    auto ans = s.productExceptSelf2(nums);
    for (uint32_t i = 0; i < ans.size(); i++) {
        if (ans[i] != expected[i]) {
            cout << "Failed testcase #" << tnum << " expected '" << expected[i] << "' at i = " << i
                 << " got '" << ans[i] << "'\n";
            return;
        }
    }
    cout << "Testcase #" << tnum << ": Passed!\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    vector<int> v{1, 2, 4, 6};
    vector<int> r{48, 24, 12, 8};
    runTests(1, v, r);

    v = vector<int>{-1, 0, 1, 2, 3};
    r = vector<int>{0, -6, 0, 0, 0};
    runTests(2, v, r);

    v = vector<int>{0, -1};
    r = vector<int>{-1, 0};
    runTests(3, v, r);

    v = vector<int>{0, 0, 0};
    r = vector<int>{0, 0, 0};
    runTests(4, v, r);

    v = vector<int>{0, 0, -1};
    r = vector<int>{0, 0, 0};
    runTests(4, v, r);

    v = vector<int>{-1, -1};
    r = vector<int>{-1, -1};
    runTests(5, v, r);

    return 0;
}
