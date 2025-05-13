// https://neetcode.io/problems/minimum-stack
// Need a better solution, this uses O(n) for pop
// Use a pair which points to the min val at each
// stage of the stack.
#include <climits>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class MinStack3 {
   public:
    vector<pair<int, int>> s;
    MinStack3() {}

    void push(int val) {
        int min_e = min(val, this->s.empty() ? val : this->getMin());
        this->s.push_back(make_pair(val, min_e));
    }

    void pop() { this->s.pop_back(); }

    int top() { return this->s[this->s.size() - 1].first; }

    int getMin() { return this->s[this->s.size() - 1].second; }
};

class MinStack2 {
   public:
    stack<pair<int, int>> s;
    MinStack2() {}

    void push(int val) {
        auto pair = make_pair(val, val);
        if (!this->s.empty())
            pair = make_pair(val, val < this->s.top().second ? val : this->s.top().second);
        this->s.push(pair);
    }

    void pop() { s.pop(); }

    int top() { return s.top().first; }

    int getMin() { return s.top().second; }
};

class MinStack {
   public:
    vector<int> s;
    int min_val;

    MinStack() { this->min_val = INT_MAX; }

    void push(int val) {
        this->s.push_back(val);
        if (val < this->min_val) this->min_val = val;
    }

    void pop() {
        this->s.pop_back();
        this->min_val = INT_MAX;
        for (const int& e : this->s) {
            if (e < this->min_val) this->min_val = e;
        }
    }

    int top() { return this->s[this->s.size() - 1]; }

    int getMin() { return this->min_val; }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    MinStack* ms = new MinStack();

    ms->push(1);
    ms->push(2);
    ms->push(0);
    cout << "min: " << ms->getMin() << "\n";
    ms->pop();
    cout << "top: " << ms->top() << "\n";
    cout << "min: " << ms->getMin() << "\n";

    cout << "=====================\n";

    MinStack2* ms2 = new MinStack2();

    ms2->push(1);
    ms2->push(2);
    ms2->push(0);
    cout << "min: " << ms2->getMin() << "\n";
    ms2->pop();
    cout << "top: " << ms2->top() << "\n";
    cout << "min: " << ms2->getMin() << "\n";

    cout << "=====================\n";

    MinStack3* ms3 = new MinStack3();

    ms3->push(1);
    ms3->push(2);
    ms3->push(0);
    cout << "min: " << ms3->getMin() << "\n";
    ms3->pop();
    cout << "top: " << ms3->top() << "\n";
    cout << "min: " << ms3->getMin() << "\n";

    return 0;
}
