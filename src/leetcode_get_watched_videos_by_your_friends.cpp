// https://leetcode.com/problems/get-watched-videos-by-your-friends/
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos,
                                          vector<vector<int>>& friends, int id, int level) {
        queue<pair<int, int>> q;
        q.push(pair<int, int>(id, 0));
        vector<bool> visited(friends.size(), false);
        visited[id] = true;
        vector<int> final_friends;

        while (!q.empty()) {
            auto f = q.front();
            q.pop();
            int curr_level = f.second;
            int curr_friend = f.first;

            if (curr_level == level) {
                final_friends.push_back(curr_friend);
                continue;
            }
            if (curr_level > level) {
                continue;
            }
            for (int& nei : friends[curr_friend]) {
                if (!visited[nei]) {
                    visited[nei] = true;
                    q.push(pair<int, int>(nei, curr_level + 1));
                }
            }
        }
        unordered_map<string, int> videos;
        for (int& i : final_friends) {
            for (auto& s : watchedVideos[i]) {
                videos[s]++;
            }
        }
        vector<pair<int, string>> videosArr;
        for (auto& p : videos) {
            videosArr.push_back(pair<int, string>(p.second, p.first));
        }
        sort(videosArr.begin(), videosArr.end(), [](auto& a, auto& b) {
            if (a.first == b.first) return a.second < b.second;
            return a.first < b.first;
        });

        vector<string> ans;
        for (auto& p : videosArr) {
            ans.push_back(p.second);
        }
        return ans;
    }
};

struct TestCase {
    vector<vector<string>> watchedVideos;
    vector<vector<int>> friends;
    int id;
    int level;
    vector<string> expected;

    std::function<vector<string>(vector<vector<string>>&, vector<vector<int>>&, int, int)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        cout << "Testcase #" << n << ": ";

        auto t1 = high_resolution_clock::now();
        vector<string> ans = func(watchedVideos, friends, id, level);
        auto t2 = high_resolution_clock::now();
        duration<double, micro> time_taken = t2 - t1;
        bool failed = false;
        for (size_t i = 0; i < ans.size(); i++) {
            if (ans[i] != expected[i]) {
                failed = true;
                cout << "Failed! - expected '" << expected[i] << "' got '" << ans[i] << "'";
            }
        }
        if (!failed) cout << "Passed!";
        cout << "\nTime taken: " << time_taken.count() << "ms" << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto watchedVideosByFriends = [&](std::vector<vector<string>>& w, vector<vector<int>>& f, int i,
                                      int l) { return s.watchedVideosByFriends(w, f, i, l); };

    vector<TestCase> testcases = {
        {vector<vector<string>>{{"A", "B"}, {"A"}}, vector<vector<int>>{{1}, {0}}, 0, 1,
         vector<string>{"A"}, watchedVideosByFriends},
        {vector<vector<string>>{{"A", "B"}, {"C"}, {"B", "C"}, {"D"}},
         vector<vector<int>>{{1, 2}, {0, 3}, {0, 3}, {1, 2}}, 0, 1, vector<string>{"B", "C"},
         watchedVideosByFriends},
        {vector<vector<string>>{{"A", "B"}, {"C"}, {"B", "C"}, {"D"}},
         vector<vector<int>>{{1, 2}, {0, 3}, {0, 3}, {1, 2}}, 0, 2, vector<string>{"D"},
         watchedVideosByFriends},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
