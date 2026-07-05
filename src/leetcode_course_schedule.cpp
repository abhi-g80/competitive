// https://leetcode.com/problems/course-schedule
// https://leetcode.com/problems/course-schedule-ii
// https://neetcode.io/problems/course-schedule
// https://neetcode.io/problems/course-schedule-ii
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solution {
   public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // prereq is like [[0,1], [2,1], ...]
        // means to take course 0 need to take course 1 first, similarly for
        // course 2
        //
        // in this case, graph would look like
        //
        //    1 -> 0
        //    1 -> 2
 
        vector<int> dependency(numCourses, 0);
        vector<vector<int>> courses(numCourses);
        for(int i = 0; i < (int)prerequisites.size(); i++) {
            dependency[prerequisites[i][0]]++;
            courses[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
        stack<int> s;

        for(int i = 0; i < numCourses; i++) if(dependency[i] == 0) s.push(i);
        if(s.size() == 0) return false;

        vector<int> ordering;
        while(!s.empty()) {
            int course = s.top(); s.pop();
            ordering.push_back(course);
            for(int i = 0; i < (int)courses[course].size(); i++) {
                int cc = courses[course][i];
                dependency[cc]--;
                if(dependency[cc] == 0) s.push(cc);
            }
        }
        printf("----\n");
        for(const int& c: ordering) printf("%d ", c);
        printf("\n----\n");
        if((int)ordering.size() == numCourses) return true;
        return false;
    };
};

struct TestCase {
    int numCourses;
    vector<vector<int>> prereq;

    bool expected;

    std::function<bool(int, vector<vector<int>>)> func;

    void run(int n) {
        using chrono::duration;
        using chrono::duration_cast;
        using chrono::high_resolution_clock;
        using chrono::microseconds;
        using chrono::milliseconds;

        cout << "Testcase #" << n << ": ";

        auto t1 = high_resolution_clock::now();
        bool ans = func(numCourses, prereq);
        auto t2 = high_resolution_clock::now();
        duration<double, micro> time_taken = t2 - t1;
        bool failed = false;
        if (ans != expected) {
            failed = true;
            cout << boolalpha << "Failed! - expected '" << expected << "' got '" << ans << "'";
        }
        if (!failed) cout << "Passed!";
        cout << " Time taken: " << time_taken.count() << "ms" << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> v;

    Solution s;

    auto canFinish = [&](int n, vector<vector<int>> p) { return s.canFinish(n, p); };

    vector<TestCase> testcases = {
        {2, vector<vector<int>>{{1,0}}, true, canFinish},
        {2, vector<vector<int>>{{1,0}, {0,1}}, false, canFinish},
        {3, vector<vector<int>>{{1,0}, {2,1}, {2,0}}, true, canFinish},
        {5, vector<vector<int>>{{1,4}, {2,4}, {3,1}, {3,2}}, true, canFinish},
        {3, vector<vector<int>>{{0, 1}, {0, 2}, {1, 2}}, true, canFinish},
        {7, vector<vector<int>>{{1, 0}, {0, 3}, {0, 2}, {3, 2}, {2, 5}, {4, 5}, {5, 6}, {2, 4}}, true, canFinish},
        {2, vector<vector<int>>{{0, 1}, {1, 0}}, false, canFinish},
        {800, vector<vector<int>>{{695, 229}, {199, 149}, {443, 397}, {258, 247}, {781, 667}, {350, 160}, {678, 629},
                                  {467, 166}, {500, 450}, {477, 107}, {483, 151}, {792, 785}, {752, 368}, {659, 623},
                                  {316, 224}, {487, 268}, {743, 206}, {552, 211}, {314, 20}, {720, 196}, {421, 103},
                                  {493, 288}, {762, 24}, {528, 318}, {472, 32}, {684, 502}, {641, 354}, {586, 480},
                                  {629, 54}, {611, 412}, {719, 680}, {733, 42}, {549, 519}, {697, 316}, {791, 634},
                                  {546, 70}, {676, 587}, {460, 58}, {605, 530}, {617, 579}, {484, 89}, {571, 482},
                                  {767, 200}, {555, 547}, {771, 695}, {624, 542}, {708, 551}, {432, 266}, {656, 468},
                                  {724, 317}, {423, 248}, {621, 593}, {781, 399}, {535, 528}, {578, 12}, {770, 549},
                                  {576, 295}, {318, 247}, {400, 372}, {465, 363}, {786, 482}, {441, 398}, {577, 411},
                                  {524, 30}, {741, 540}, {459, 59}, {758, 96}, {550, 89}, {402, 295}, {476, 336}, {645, 346},
                                  {750, 116}, {551, 207}, {343, 226}, {568, 498}, {530, 228}, {525, 84}, {507, 128},
                                  {526, 210}, {535, 381}, {635, 330}, {654, 535}, {710, 275}, {397, 213}, {412, 44},
                                  {131, 70}, {508, 49}, {679, 223}, {519, 11}, {626, 286}, {242, 160}, {778, 199}, {606, 281},
                                  {226, 16}, {340, 46}, {578, 127}, {212, 208}, {674, 343}, {778, 108}}, true, canFinish},
        {10, vector<vector<int>>{{5, 8}, {3, 5}, {1, 9}, {4, 5}, {0, 2}, {7, 8}, {4, 9}}, true, canFinish},
        {2, vector<vector<int>>{{1, 0}}, true, canFinish},
        {4, vector<vector<int>>{{1, 0}, {2, 0}, {3, 1}, {3, 2}}, true, canFinish},
};
    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
