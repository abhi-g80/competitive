// https://open.kattis.com/problems/anotherbrick
#include <iostream>

using namespace std;

void solve() {
    int h, w, n;
    cin >> h >> w >> n;
    int rt = 0, l = 0, r = 0;
    int *nums = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        rt += nums[i];
        if (rt == w) {
            l += 1, rt = 0;
        }
        if (l == h) r = 1;
    }
    if (r)
        cout << "YES";
    else
        cout << "NO";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    solve();
    return 0;
}
