// https://neetcode.io/problems/valid-sudoku
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int box(int x, int y) {
    if (0 <= x && x <= 2) {
        if (0 <= y && y <= 2) return 1;
        if (3 <= y && y <= 5) return 2;
        if (6 <= y && y <= 8) return 3;
    }
    if (3 <= x && x <= 5) {
        if (0 <= y && y <= 2) return 4;
        if (3 <= y && y <= 5) return 5;
        if (6 <= y && y <= 8) return 6;
    }
    if (0 <= y && y <= 2) return 7;
    if (3 <= y && y <= 5) return 8;
    return 9;
}

class Solution {
   public:
    bool isValidSudoku2(vector<vector<char>>& board) {
        vector<int> row_check(10, 1 << 10);
        vector<int> column_check(10, 1 << 10);
        vector<int> box_check(10, 1 << 10);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;

                int elem = board[i][j] - '0';
                if (elem <= 0 || elem > 9)
                    throw invalid_argument("board contains values outside of sudoku range (1-9)");

                int r, c, b;
                int v = box(i, j);

                r = row_check[i + 1] & (1 << elem);
                c = column_check[j + 1] & (1 << elem);
                b = box_check[v] & (1 << elem);

                if ((r == (1 << elem)) || (c == (1 << elem)) || (b == (1 << elem))) return false;

                row_check[i + 1] ^= (1 << elem);
                column_check[j + 1] ^= (1 << elem);
                box_check[v] ^= (1 << elem);
            }
        }
        return true;
    }
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_map<int, vector<int>> row_check;
        unordered_map<int, vector<int>> column_check;
        unordered_map<int, vector<int>> box_check;

        for (int i = 0; i < 10; i++) {
            row_check[i + 1] = vector<int>(10, 0);
            column_check[i + 1] = vector<int>(10, 0);
            box_check[i + 1] = vector<int>(10, 0);
        }

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;

                int elem = board[i][j] - '0';
                if (elem <= 0 || elem > 9)
                    throw invalid_argument("board contains values outside of sudoku range (1-9)");

                row_check[i + 1][elem] += 1;
                if (row_check[i + 1][elem] > 1) return false;

                column_check[j + 1][elem] += 1;
                if (column_check[j + 1][elem] > 1) return false;

                box_check[box(i, j)][elem] += 1;
                if (box_check[box(i, j)][elem] > 1) return false;
            }
        }

        return true;
    }
};

struct TestCase {
    vector<vector<char>> v;
    bool expected;

    std::function<bool(vector<vector<char>>&)> func;

    void run(int i) {
        bool ans = func(v);
        if (ans != expected) {
            cout << boolalpha << "Testcase #" << i << ": Failed! - expected '" << expected
                 << "' got '" << ans << "'\n";
            return;
        }
        cout << "Testcase #" << i << ": Passed!\n";
    }
};

int main() {
    Solution s;
    // clang-format off
    vector<vector<char>> board1 {
         {'1','2','.','.','3','.','.','.','.'},
         {'4','.','.','5','.','.','.','.','.'},
         {'.','9','8','.','.','.','.','.','3'},
         {'5','.','.','.','6','.','.','.','4'},
         {'.','.','.','8','.','3','.','.','5'},
         {'7','.','.','.','2','.','.','.','6'},
         {'.','.','.','.','.','.','2','.','.'},
         {'.','.','.','4','1','9','.','.','8'},
         {'.','.','.','.','8','.','.','7','9'}
    };
    vector<vector<char>> board2 {
         {'1','2','.','.','3','.','.','.','.'},
         {'4','.','.','5','.','.','.','.','.'},
         {'.','9','1','.','.','.','.','.','3'},
         {'5','.','.','.','6','.','.','.','4'},
         {'.','.','.','8','.','3','.','.','5'},
         {'7','.','.','.','2','.','.','.','6'},
         {'.','.','.','.','.','.','2','.','.'},
         {'.','.','.','4','1','9','.','.','8'},
         {'.','.','.','.','8','.','.','7','9'}
    };
    vector<vector<char>> board3 {
         {'5','3','.','.','7','.','.','.','.'},
         {'6','.','.','1','9','5','.','.','.'},
         {'.','9','8','.','.','.','.','6','.'},
         {'8','.','.','.','6','.','.','.','3'},
         {'4','.','.','8','.','3','.','.','1'},
         {'7','.','.','.','2','.','.','.','6'},
         {'.','6','.','.','.','.','2','8','.'},
         {'.','.','.','4','1','9','.','.','5'},
         {'.','.','.','.','8','.','.','7','9'},
    };
    vector<vector<char>> board4 {
        {'.','.','4','.','.','.','6','3','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'5','.','.','.','.','.','.','9','.'},
        {'.','.','.','5','6','.','.','.','.'},
        {'4','.','3','.','.','.','.','.','1'},
        {'.','.','.','7','.','.','.','.','.'},
        {'.','.','.','5','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'}
    };
    // clang-format on

    auto isValidSudoku = [&](std::vector<vector<char>>& v) { return s.isValidSudoku(v); };
    auto isValidSudoku2 = [&](std::vector<vector<char>>& v) { return s.isValidSudoku2(v); };

    vector<TestCase> testcases = {
        {board1, true, isValidSudoku},  {board1, true, isValidSudoku2},
        {board2, false, isValidSudoku}, {board2, false, isValidSudoku2},
        {board3, true, isValidSudoku},  {board3, true, isValidSudoku2},
        {board4, false, isValidSudoku}, {board4, false, isValidSudoku2},
    };

    int i = 1;
    for (auto& testCase : testcases) {
        testCase.run(i++);
    }

    return 0;
}
