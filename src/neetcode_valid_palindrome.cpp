// https://neetcode.io/problems/is-palindrome
#include <functional>
#include <iostream>
#include <string>

using namespace std;

class Solution {
   public:
    bool isPalindrome(string s) {
        for (int32_t i = 0, j = s.size() - 1; i < j; i++, j--) {
            while (i < s.size() && !isalnum(s[i])) i++;
            while (j >= 0 && !isalnum(s[j])) j--;
            if (i >= j) return true;
            if (tolower(s[i]) != tolower(s[j])) return false;
        }
        return true;
    }
};

struct TestCase {
    string s;
    bool expected;

    function<bool(string)> func;

    void run(int n) {
        bool ans = func(s);
        if (ans != expected) {
            cout << boolalpha << "Testcase #" << n << ": Failed! - expected '" << expected
                 << "' got '" << ans << "'\n";
            return;
        }
        cout << "Testcase #" << n << ": Passed!\n";
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    Solution s;

    auto isPalindrome = [&](string x) { return s.isPalindrome(x); };

    vector<TestCase> testcases = {
        {"Was it a car or a cat I saw", true, isPalindrome},
        {"tab a caT", false, isPalindrome},
        {"ab BA", true, isPalindrome},
        {"No lemon, no melon", true, isPalindrome},
        {".,", true, isPalindrome},
        {".", true, isPalindrome},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }
    return 0;
}
