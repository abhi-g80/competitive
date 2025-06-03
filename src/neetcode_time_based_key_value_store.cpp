// https://neetcode.io/problems/time-based-key-value-store
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class TimeMap {
   public:
    unordered_map<string, vector<pair<string, int>>> m;
    TimeMap() {}

    void set(string key, string value, int timestamp) {
        if (m.find(key) == m.end()) {
            vector<pair<string, int>> v;
            v.push_back({value, timestamp});
            this->m[key] = v;
        }
        this->m[key].push_back({value, timestamp});
    }

    string get(string key, int timestamp) {
        if (this->m.find(key) == this->m.end()) return "";
        int32_t l = 0, r = m[key].size() - 1;
        int32_t mid = l + (r - l) / 2;
        string res;
        while (l <= r) {
            mid = l + (r - l) / 2;
            if (m[key][mid].second <= timestamp) {
                res = m[key][mid].first;
                l = mid + 1;
            } else
                r = mid - 1;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    TimeMap* tm = new TimeMap();

    tm->set("key1", "value1", 1);
    cout << "get(\"key1\", 1): " << tm->get("key1", 1) << "\n";
    cout << "get(\"key1\", 10): " << tm->get("key1", 10) << "\n";
    cout << "get(\"key1\", 11): " << tm->get("key1", 11) << "\n";
    cout << "get(\"key1\", 12): " << tm->get("key1", 12) << "\n";
    cout << "get(\"key1\", 20): " << tm->get("key1", 20) << "\n";
    tm->set("key1", "value2", 10);
    cout << "get(\"key1\", 10): " << tm->get("key1", 10) << "\n";
    cout << "get(\"key1\", 11): " << tm->get("key1", 11) << "\n";
    cout << "get(\"key1\", 12): " << tm->get("key1", 12) << "\n";
    cout << "get(\"key1\", 20): " << tm->get("key1", 20) << "\n";
    cout << "=====================\n";

    // ["TimeMap", "set", ["x", "y", 100], "get", ["x", 99], "get", ["x", 100], "get", ["x", 101]]
    //

    delete tm;
    tm = new TimeMap();

    tm->set("x", "y", 100);
    cout << "get(\"x\", 99): " << tm->get("x", 99) << "\n";
    cout << "get(\"x\", 100): " << tm->get("x", 100) << "\n";
    cout << "get(\"x\", 101): " << tm->get("x", 101) << "\n";
    cout << "=====================\n";

    delete tm;
    tm = new TimeMap();

    // ["TimeMap","set","set","get","get","get","get","get"]
    // [[],["love","high",10],["love","low",20],["love",5],["love",10],["love",15],["love",20],["love",25]]

    tm->set("love", "high", 10);
    tm->set("love", "low", 20);
    cout << "get(\"love\",  5): " << tm->get("love", 5) << "\n";
    cout << "get(\"love\", 10): " << tm->get("love", 10) << "\n";
    cout << "get(\"love\", 15): " << tm->get("love", 15) << "\n";
    cout << "get(\"love\", 20): " << tm->get("love", 20) << "\n";
    cout << "get(\"love\", 25): " << tm->get("love", 25) << "\n";
    return 0;
}
