// https://neetcode.io/problems/car-fleet
#include <functional>
#include <iostream>
#include <cstdint>

using namespace std;

class Solution {
   public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // target: 10 pos: [1,4] speed: [3,2]
        // for 1st car dist = 10 - 1 = 9 which can be covered in 9/3 = 3 times
        // for 2nd car dist = 10 - 4 = 6 which can be covered in 6/2 = 3 times
        // so both car meet at dest at the same time, so 1 fleet.
        //
        // target: 10 pos: [4,2,0,7,1] speed: [2,2,1,1,9]
        // for 1st car dist = 10-4 = 6/2 = 3
        // for 2nd car dist = 10-2 = 8/2 = 4 ?
        // for 3rd car dist = 10-0 = 10/1 = 10
        // for 4th car dist = 10-7 = 3/1 = 3
        // for 5th car dist = 10-1 = 9/9 = 1
        //
        // 3rd 5th 2nd   1st      4th
        // 10  1    4     3        3

        vector<float> time_pos(target + 1, -1.0);
        for (uint32_t i = 0; i < position.size(); i++) {
            time_pos[position[i]] = (float)(target - position[i]) / speed[i];
        }
        int fleets = 1;
        float comp = -1.0;
        for (int32_t i = time_pos.size() - 1; i >= 0; i--) {
            if (time_pos[i] != -1 && comp == -1.0) {
                comp = time_pos[i];
            }
            if (comp == -1.0) continue;
            if (time_pos[i] > comp) {
                fleets++;
                comp = time_pos[i];
            }
        }
        return fleets;
    }
};

struct TestCase {
    int target;
    vector<int> position;
    vector<int> speed;
    int expected;

    function<int(int, vector<int>&, vector<int>&)> func;

    void run(int n) {
        int ans = func(target, position, speed);
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

    auto carFleet = [&](int t, vector<int>& pos, vector<int>& sp) {
        return s.carFleet(t, pos, sp);
    };

    vector<TestCase> testcases = {
        // clang-format off
        {10, vector<int>{1,4}, vector<int>{3,5}, 2, carFleet},
        {10, vector<int>{1,4}, vector<int>{3,2}, 1, carFleet},
        {10, vector<int>{4,1,0,7}, vector<int>{2,2,1,1}, 3, carFleet},
        {10, vector<int>{4,2,0,7,1}, vector<int>{2,2,1,1,9}, 3, carFleet},
        // clang-format on
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }
    return 0;
}
