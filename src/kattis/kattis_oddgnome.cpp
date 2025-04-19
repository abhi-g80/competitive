// https://open.kattis.com/problems/oddgnome
#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, t, c, k, p = -1, prev = -1;
    cin >> n;
    while (n--) {
        cin >> t;
        vector<int> nums;
        while (t--) {
            cin >> k;
            nums.push_back(k);
        }
        for (int i = 1; i < nums.size(); i++) {
            p = nums[i - 1] - nums[i];
            if (p * prev < 0) {
                c = i;
                if ((i < nums.size() - 1) && (nums[i - 1] - nums[i + 1]) * prev > 0) c = i + 1;
                break;
            }
            prev = p;
        }
        cout << c << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
