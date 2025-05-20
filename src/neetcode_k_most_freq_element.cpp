// https://neetcode.io/problems/top-k-elements-in-list
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (auto i : nums) freq[i]++;

        vector<vector<int>> v(nums.size() + 1);
        for (auto i : freq) v[i.second].push_back(i.first);

        vector<int> res;
        for (int i = nums.size(), j = 0; j < k && i >= 0; i--) {
            if (v[i].size() != 0) {
                for (auto f : v[i]) {
                    res.push_back(f);
                    j++;
                }
            }
        }
        return res;
    }
};

Solution s;

void runTests(vector<int>& nums, int k, int tnum, vector<int>& expected) {
    auto ans = s.topKFrequent(nums, k);
    sort(ans.begin(), ans.end());

    for (uint32_t i = 0; i < ans.size(); i++) {
        if (ans[i] != expected[i]) {
            cout << "Failed testcase #" << tnum << "expected '" << expected[i] << "' at i = " << i
                 << " got '" << ans[i] << "\n";
            return;
        }
    }
    cout << "Testcase #" << tnum << ": Passed!\n";
}

int main() {
    vector<int> v{1, 1, 1, 2, 2, 3};
    vector<int> e{1, 2};
    int k = 2;

    runTests(v, k, 1, e);

    v = vector<int>{1, 2};
    k = 2;
    runTests(v, k, 2, e);

    v = vector<int>{7, 7};
    k = 1;
    e = vector<int>{7};
    runTests(v, k, 3, e);
}
