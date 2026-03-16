// Source: https://leetcode.com/problems/n-queens/   |   Difficulty: Hard
//
// Problem Description:
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
//
// Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
//
// Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.
//
// Example:
// Input: n = 4
// Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
// Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
//
// Constraints:
// 1 <= n <= 9
//

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> results;
        vector<string> board(n, string(n, '.'));
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false); // row + col
        vector<bool> diag2(2 * n - 1, false); // row - col + (n - 1)

        function<void(int)> backtrack = [&](int row) {
            if (row == n) {
                results.push_back(board);
                return;
            }
            for (int col = 0; col < n; ++col) {
                if (cols[col] || diag1[row + col] || diag2[row - col + n - 1]) {
                    continue;
                }
                board[row][col] = 'Q';
                cols[col] = diag1[row + col] = diag2[row - col + n - 1] = true;

                backtrack(row + 1);

                board[row][col] = '.';
                cols[col] = diag1[row + col] = diag2[row - col + n - 1] = false;
            }
        };

        backtrack(0);
        return results;         
    }
};
