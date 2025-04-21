// https://open.kattis.com/problems/basicprogramming1
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

void solve() {
    int n, inst;
    cin >> n >> inst;
    vector<int> nums(n);
    vector<int> visited(n);
    int sum = 0;
    for (int i = 0; i < n; i++) cin >> nums[i];

    switch (inst) {
        case 1:
            cout << 7;
            break;
        case 2:
            nums[0] > nums[1]    ? cout << "Bigger"
            : nums[0] == nums[1] ? cout << "Equal"
                                 : cout << "Smaller";
            break;
        case 3:
            cout << max(min(nums[0], nums[1]), min(max(nums[0], nums[1]), nums[2]));
            break;
        case 4:
            cout << accumulate(nums.begin(), nums.end(), 0);
            break;
        case 5:
            // for(int i = 0; i < nums.size() && ((nums[i] % 2) == 0); i++) sum += nums[i];
            for (int i = 0; i < nums.size(); i++) {
                if ((nums[i] & 2) == 0) sum += nums[i];
            }
            cout << sum;
            break;
        case 6:
            for (int i = 0; i < nums.size(); i++) {
                cout << (char)('a' + (nums[i] % 26));
            }
            break;
        case 7:
            visited[0] = 1;
            for (int i = 0;; i = nums[i]) {
                if (i >= nums.size()) {
                    cout << "Out";
                    break;
                }
                if (i == nums.size() - 1) {
                    cout << "Done";
                    break;
                }
                if (visited[i] == 1) {
                    cout << "Cyclic";
                    break;
                }
                visited[i] = 1;
            }
            break;
        default:
            break;
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
