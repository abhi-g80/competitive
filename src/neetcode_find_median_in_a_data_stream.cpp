// https://neetcode.io/problems/find-median-in-a-data-stream
#include <iostream>
#include <queue>
#include <vector>
#include <cstdint>

using namespace std;

class MedianFinder {
    priority_queue<int, vector<int>, less<int>> left;      // max heap on left of median
    priority_queue<int, vector<int>, greater<int>> right;  // min heap on right of median

    double curr_median;

   public:
    MedianFinder() {}
    void addNum(int num) {
        // cout << "adding " << num << " curr_median = " << curr_median << "\n";
        if (left.size() == 0 && right.size() == 0) {
            left.push(num);
            curr_median = num;
        } else if (num <= curr_median)
            left.push(num);
        else
            right.push(num);

        while (!right.empty() && (right.size() - left.size() > 1)) {
            left.push(right.top());
            right.pop();
        }
        while (!left.empty() && (left.size() - right.size() > 1)) {
            right.push(left.top());
            left.pop();
        }

        // if(right.size() == 0 && left.size() == 2) {
        //     right.push(left.top());
        //     left.pop();
        // }

        if (!left.empty() && !right.empty()) curr_median = findMedian();

        while (!left.empty() && (left.top() > curr_median)) {
            right.push(left.top());
            left.pop();
        }
        while (!right.empty() && (right.top() < curr_median)) {
            left.push(right.top());
            right.pop();
        }
    }

    double findMedian() {
        // int a = left.top();
        // int b = right.top();
        // cout << a << " " <<  b << "\n";
        // cout << "lsize " << left.size() << " rsize " << right.size() << " curr_median " <<
        // curr_median <<  "\n";
        if (left.size() == right.size()) {
            // cout << "size same " << (left.top()+right.top()) * 0.5;
            int l = left.top();
            int r = right.top();
            // cout << "ltop = " << l << " rtop " << r << "\n";
            curr_median = (l + r) * 0.5;
        } else if (left.size() > right.size())
            curr_median = left.top();
        else
            curr_median = right.top();
        return curr_median;
        // return 1.0;
    }

    // double findMedian() {
    //     int l = this->left.top();
    //     int r = this->right.top();

    //     cout << l << r << "\n\n";

    //     if(this->left.size() == this->right.size()) return (l+r)*0.5;
    //     else if(this->left.size() > this->right.size()) return l;
    //     else return r;
    // }
};

enum Commands { AddNum, FindMedian };

struct TestCase {
    vector<int> input;
    vector<double> expected;
    MedianFinder* m;

    void run(int n) {
        cout << "Testcase #: " << n << " ";
        for (uint32_t i = 0, j = 0; i < input.size() && j < expected.size(); i++) {
            switch (input[i]) {
                case AddNum:
                    m->addNum(input[++i]);
                    break;
                case FindMedian:
                    double median = m->findMedian();
                    double exp = expected[j++];
                    if (median != exp) {
                        cout << boolalpha << "Failed! - expected '" << exp << "' got '" << median
                             << "' for FindMedian at index " << i + 1 << "\n";
                        return;
                        break;
                    }
            }
        }
        cout << "Passed\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    MedianFinder m;

    vector<TestCase> testcases = {
        {
            .input = {AddNum, 1, FindMedian, AddNum, 3, FindMedian, AddNum, 2, FindMedian},
            .expected = {1.0, 2.0, 2.0},
            .m = new MedianFinder(),
        },
        {
            .input = {AddNum, -1, FindMedian, AddNum, 3, FindMedian, AddNum, -2, FindMedian},
            .expected = {-1.0, 1.0, -1.0},
            .m = new MedianFinder(),
        },
        {
            .input = {AddNum, 5, AddNum, 3, FindMedian, AddNum, 7, FindMedian, AddNum, 2,
                      FindMedian},
            .expected = {4, 5, 4},
            .m = new MedianFinder(),
        },
        {
            .input = {AddNum, 5, AddNum, 6, FindMedian, AddNum, 7, FindMedian, AddNum, 2,
                      FindMedian, AddNum, 7, AddNum, 8, FindMedian},
            .expected = {5.5, 6, 5.5, 6.5},
            .m = new MedianFinder(),
        },
        {
            .input = {AddNum, 6, AddNum, 4, AddNum, 3, AddNum, 2, FindMedian},
            .expected = {3.5},
            .m = new MedianFinder(),
        },
    };

    int i = 1;
    for (auto& x : testcases) x.run(i++);

    return 0;
}
