// https://neetcode.io/problems/products-of-array-discluding-self
#include <algorithm>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int longestConsecutive_hashmapAndSet(vector<int>& nums) {
        int res = 0;
        unordered_map<int, int> chain;
        unordered_map<int, bool> visited;

        for (const auto& i : nums) chain[i] = 0;

        for (uint32_t i = 0; i < nums.size(); i++) {
            if (visited.find(nums[i]) == visited.end()) {
                visited[nums[i]] = true;
            } else if (visited[nums[i]])
                continue;
            int j = nums[i];
            while (chain.find(j) != chain.end()) {
                chain[j--]++;
            }
        }
        for (const auto& i : chain) {
            if (res < i.second) res = i.second;
        }
        return res;
    }
    int longestConsecutive_sort(vector<int>& nums) {
        int res = 1, l = 1;

        uint32_t s = nums.size();
        if (s <= 1) return s;

        sort(nums.begin(), nums.end());

        for (uint32_t i = 1; i <= s - 1; i++) {
            if (nums[i] - nums[i - 1] == 0) {
                continue;
            }
            if ((nums[i] - nums[i - 1]) != 1) {
                if (res < l) res = l;
                l = 1;
            } else
                l++;
            if ((i == s - 1) && (res <= l)) res = l;
        }
        return res;
    }
};

struct TestCase {
    vector<int> v;
    int expected;

    std::function<int(vector<int>&)> func;

    void run(int i) {
        auto ans = func(v);
        if (ans != expected) {
            cout << "Testcase #" << i << ": Failed! - expected '" << expected << "' got '" << ans
                 << "'\n";
            return;
        }
        cout << "Testcase #" << i << ": Passed!\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto hashmapAndSet = [&](std::vector<int>& v) { return s.longestConsecutive_hashmapAndSet(v); };

    vector<TestCase> testcases = {
        // clang-format off
        {vector<int>{2, 20, 4, 10, 3, 4, 5}, 4, hashmapAndSet},
        {vector<int>{2, 20, 4, 10, 3, 4, 5}, 4, hashmapAndSet},
        {vector<int>{0, 3, 2, 5, 4, 6, 1, 1}, 7, hashmapAndSet},
        {vector<int>{-1, 0, 1, 2, 3}, 5, hashmapAndSet},
        {vector<int>{-2, 0, 1, 2, 3}, 4, hashmapAndSet},
        {vector<int>{9, 1, -3, 2, 4, 8, 3, -1, 6, -2, -4, 7}, 4, hashmapAndSet},
        {vector<int>{9, 1, 4, 7, 3, -1, 0, 5, 8, -1, 6}, 7, hashmapAndSet},
        {vector<int>{}, 0, hashmapAndSet},
        {vector<int>{0, 0}, 1, hashmapAndSet},
        // clang-format on
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
