// https://neetcode.io/problems/kth-largest-element-in-a-stream
#include <iostream>
#include <queue>
#include <vector>
#include <cstdint>

using namespace std;

class KthLargest {
   private:
    priority_queue<int, vector<int>, greater<int>> pq;  // min heap
    uint32_t k;

   public:
    KthLargest(int k, vector<int>& nums) {
        this->k = (uint32_t)k;
        for (int v : nums) {
            this->pq.push(v);
            if (this->pq.size() > this->k) {
                this->pq.pop();
            }
        }
    }

    int add(int val) {
        this->pq.push(val);
        if (this->pq.size() > this->k) {
            this->pq.pop();
        }
        return this->pq.top();
    }
};

enum Commands { AddNum };

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    vector<int> nums = vector<int>{1, 2, 3, 3};
    KthLargest m(3, nums);

    vector<int> commands = vector<int>{AddNum, 3, AddNum, 5, AddNum, 6, AddNum, 7, AddNum, 8};

    for (uint32_t i = 0; i < commands.size(); i++) {
        if (commands[i] == AddNum) cout << m.add(commands[++i]) << "\n";
    }

    return 0;
}
